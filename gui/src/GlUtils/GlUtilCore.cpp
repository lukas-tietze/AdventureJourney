#include "GlUtils.hpp"
#include "data/Io.hpp"
#include <cstring>

const glutil::CreateInfo glutil::DefaultCreateInfo = {
    ""};

namespace
{
//window:
GLFWwindow *win = nullptr;
int w = 0;
int h = 0;

//mouse
int mouseX = 0;
int mouseY = 0;
int mouseDeltaX = 0;
int mouseDeltaY = 0;
float scrollX = 0;
float scrollY = 0;
bool mouseState[GLFW_MOUSE_BUTTON_LAST];
bool lastMouseState[GLFW_MOUSE_BUTTON_LAST];

//keys
bool keyState[GLFW_KEY_LAST];
bool lastKeyState[GLFW_KEY_LAST];

glutil::GlWatch<> *watch[2];

double totalTime = 0;
double delta = 0;
double lastUpdateTime = 0;

unsigned long frameCount = 0;
double cpuTime = 0;
double gpuTime = 0;

std::string windowTitle;

glutil::Screen *activeScreen;
glutil::Screen *nextScreen;
glutil::Screen *blankScreen;

void HandleResize(GLFWwindow *win, int w, int h)
{
    w = w;
    h = h;
}

void HandleScroll(GLFWwindow *win, double xoffset, double yoffset)
{
    scrollX = static_cast<float>(xoffset);
    scrollY = static_cast<float>(yoffset);
}

void HandleKeyboard(GLFWwindow *win, int key, int /*scancode*/, int action, int mods)
{
    if (key < 0 || key > GLFW_KEY_LAST)
    {
        //invalid key code
        return;
    }

    keyState[key] = action != GLFW_RELEASE;
}

void HandleMouseButton(GLFWwindow *win, int button, int action, int mods)
{
    if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST)
    {
        //invalid button code
        return;
    }

    mouseState[button] = action == GLFW_RELEASE;
}

void HandleCursor(GLFWwindow *win, double x, double y)
{
    mouseDeltaX = x - mouseX;
    mouseDeltaY = y - mouseY;
    mouseX = x;
    mouseY = y;
}

} // namespace
namespace
{
void *GetProcAddressWrapper(const char *name, void *user_ptr)
{
    return reinterpret_cast<void *>(glfwGetProcAddress(name));
}

bool InitGlfw(const glutil::CreateInfo &info)
{
    if (!glfwInit())
        return false;

    GLFWmonitor *monitor = nullptr;

    /* request a OpenGL 4.3 core profile context */
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* create the window and the gl context */
    win = glfwCreateWindow(800, 800,
                           "CG2 Application",
                           monitor,
                           nullptr);

    if (!win)
        return false;

    /* register our callbacks */
    glfwSetFramebufferSizeCallback(win, HandleResize);
    glfwSetKeyCallback(win, HandleKeyboard);
    glfwSetMouseButtonCallback(win, HandleMouseButton);
    glfwSetScrollCallback(win, HandleScroll);
    glfwSetCursorPosCallback(win, HandleCursor);

    /* make the context the current context (of the current thread) */
    glfwMakeContextCurrent(win);

    /* initialize glad (our opengl loader) */
    if (!gladLoadGL(GetProcAddressWrapper, nullptr))
    {
        util::err.WriteLine("failed to intialize glad!");
        return false;
    }

    /* just make sure we got a >= 4.3 context */
    if (!GLAD_GL_VERSION_4_3)
    {
        util::out.WriteLine("Did not get a GL >= 4.3 context!");
        return false;
    }

    /* print some information about the gl context */
    util::out.WriteLine("GL_VERSION  : %", glGetString(GL_VERSION));
    util::out.WriteLine("GL_VENDOR   : %", glGetString(GL_VENDOR));
    util::out.WriteLine("GL_RENDERER : %", glGetString(GL_RENDERER));
    util::out.WriteLine("GLSL_VERSION: %", glGetString(GL_SHADING_LANGUAGE_VERSION));

    /* reset the cursor to the window center */
    int w, h;
    glfwGetFramebufferSize(win, &w, &h);
    glfwSetCursorPos(win, w / 2, h / 2);

    return true;
}

bool InitGlState(const glutil::CreateInfo &info)
{
    glClearColor(0.7f, 0.4f, 0.4f, 1.0f);
}

bool InitData(const glutil::CreateInfo &info)
{
    watch[0] = new glutil::GlWatch<>();
    watch[1] = new glutil::GlWatch<>();
    cpuTime = 0;
    gpuTime = 0;
    frameCount = 0;

    windowTitle = info.windowTitle;

    blankScreen = new glutil::Screen();
    nextScreen = activeScreen = blankScreen;

    return true;
}
} // namespace

bool glutil::Init(CreateInfo info)
{
    return InitGlfw(info) &&
           InitGlState(info) &&
           InitData(info);
}

bool glutil::DestroyGlContext()
{
    delete watch[0];
    delete watch[1];

    glfwDestroyWindow(win);
    glfwTerminate();

    win = nullptr;
}

void glutil::UpdateTitle()
{
    auto timePassed = totalTime - lastUpdateTime;

    glfwSetWindowTitle(win, util::Format("% [fps: %, cpu: %, gpu: %]",
                                         windowTitle,
                                         frameCount / timePassed,
                                         cpuTime / timePassed,
                                         gpuTime / timePassed)
                                .c_str());
}

void glutil::Quit()
{
    glfwSetWindowShouldClose(win, true);
}

namespace
{
void ResetEventBuffers()
{
    std::memcpy(lastKeyState, keyState, sizeof(bool) * GLFW_KEY_LAST);
    std::memcpy(lastMouseState, mouseState, sizeof(bool) * GLFW_MOUSE_BUTTON_LAST);
    //TODO: Clear Event queue
}

void SwapScreen()
{
    if (activeScreen == nextScreen)
        return;

    if (activeScreen != nullptr)
        activeScreen->OnHide();

    activeScreen = nextScreen;
    activeScreen->OnShow();

    util::dbg.WriteLine("Now showing [%] (blank=%)", activeScreen, activeScreen == blankScreen);
}
} // namespace

void glutil::Loop()
{
    auto timeStamp = glfwGetTime();

    while (!glfwWindowShouldClose(win))
    {
        auto now = glfwGetTime();
        delta = now - timeStamp;
        timeStamp = now;

        totalTime += delta;
        frameCount++;

        if (totalTime - lastUpdateTime > 0.5)
        {
            UpdateTitle();
            lastUpdateTime = totalTime;
            cpuTime = 0;
            gpuTime = 0;
            frameCount = 0;
        }

        SwapScreen();

        glfwPollEvents();

        activeScreen->Update(delta);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        activeScreen->Render();

        gpuTime += watch[1]->get_gpu_time_in_ms() -
                   watch[0]->get_gpu_time_in_ms();

        cpuTime += watch[1]->get_cpu_time_in_ms() -
                   watch[0]->get_cpu_time_in_ms();

        glfwSwapBuffers(win);

        ResetEventBuffers();
    }
}

//-----------------------------------------------------------------------------------------
//Screens
//-----------------------------------------------------------------------------------------
void glutil::RequestNextScreen(Screen *s)
{
    if (s != nullptr)
        nextScreen = s;
}

void glutil::RequestBlankScreen()
{
    nextScreen = blankScreen;
}

//-----------------------------------------------------------------------------------------
//Screens
//-----------------------------------------------------------------------------------------

bool glutil::HasNextEvent()
{
    return true;
}

const glutil::Event &glutil::QueryNextEvent()
{
    return glutil::Event();
}

bool glutil::IsKeyDown(int key)
{
    return keyState[key];
}

bool glutil::IsKeyUp(int key)
{
    return !keyState[key];
}

bool glutil::WasKeyPressed(int key)
{
    return keyState[key] && !lastKeyState[key];
}

bool glutil::WasKeyReleased(int key)
{
    return !keyState[key] && lastKeyState[key];
}

bool glutil::IsButtonDown(int button)
{
    return mouseState[button];
}

bool glutil::IsButtonUp(int button)
{
    return !mouseState[button];
}

bool glutil::WasButtonPressed(int button)
{
    return mouseState[button] && !lastMouseState[button];
}

bool glutil::WasButtonReleased(int button)
{
    return !mouseState[button] && lastMouseState[button];
}
