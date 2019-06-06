#include "GlScreens.hpp"
#include "DummyData.hpp"
#include "data/Io.hpp"
#include "glm/gtx/transform.hpp"
#include "data/Random.hpp"
#include "graphics/Color.hpp"

namespace
{
constexpr char MAIN_CAM[] = "MAIN_CAM";
} // namespace

gui::DebugScreenBase::DebugScreenBase() : scene(),
                                          objects(),
                                          mouseCaptured(false),
                                          animationPaused(false),
                                          wireMode(false),
                                          cullMode(false)
{
    auto camera = this->scene.GetCamera(MAIN_CAM);
    camera->SetViewDirection(glm::vec3(1.f, 0.f, 0.f));
    camera->SetPosition(glm::vec3(0.f, 0.f, 0.f));
    camera->SetUp(glutil::AXIS_Y);
    camera->SetBindingTarget(1);
    camera->CreateGlObjects();

    this->scene.SetActiveCamera(MAIN_CAM);
    this->cameraUpdater.SetCamera(camera);

    this->scene.InitProgramFromSources(COLOR_PROG,
                                       {
                                           "assets/shaders/base/full.vert",
                                           "assets/shaders/vertex/simple.vert",
                                           "assets/shaders/base/color.frag",
                                           "assets/shaders/fragment/lightingPhong.frag",
                                           "assets/shaders/fragment/materialPropsSimple.frag",
                                           "assets/shaders/fragment/normalAttrib.frag",
                                           "assets/shaders/fragment/textureOnly.frag",
                                       });

    this->scene.InitProgramFromSources(DEBUG_TEX_PROG,
                                       {
                                           "assets/shaders/base/full.vert",
                                           "assets/shaders/vertex/simple.vert",
                                           "assets/shaders/base/color.frag",
                                           "assets/shaders/fragment/lightingDebugTexCoord.frag",
                                           "assets/shaders/fragment/materialPropsSimple.frag",
                                           "assets/shaders/fragment/normalAttrib.frag",
                                           "assets/shaders/fragment/textureOnly.frag",
                                       });

    this->scene.InitProgramFromSources(DEBUG_NRM_PROG,
                                       {
                                           "assets/shaders/base/full.vert",
                                           "assets/shaders/vertex/simple.vert",
                                           "assets/shaders/base/color.frag",
                                           "assets/shaders/fragment/lightingDebugNrm.frag",
                                           "assets/shaders/fragment/materialPropsSimple.frag",
                                           "assets/shaders/fragment/normalAttrib.frag",
                                           "assets/shaders/fragment/textureOnly.frag",
                                       });

    this->scene.InitProgramFromSources(DEPTH_PROG,
                                       {
                                           "assets/shaders/base/positionOnly.vert",
                                           "assets/shaders/vertex/simple.vert",
                                           "assets/shaders/base/depth.frag",
                                           "assets/shaders/fragment/textureOnly.frag",
                                       });

    this->scene.InitProgramFromSources(PIXEL_PROG,
                                       {
                                           "assets/shaders/postProcessing/pp.vert",
                                           "assets/shaders/postProcessing/pixelate.frag",
                                       });

    this->scene.InitProgramFromSources(BLUR_PROG,
                                       {
                                           "assets/shaders/postProcessing/pp.vert",
                                           "assets/shaders/postProcessing/blur.frag",
                                       });

    this->scene.InitProgramFromSources(DEPTH_BLUR_PROG,
                                       {
                                           "assets/shaders/postProcessing/pp.vert",
                                           "assets/shaders/postProcessing/depthBlur.frag",
                                       });

    this->scene.InitProgramFromSources(EDGE_PROG,
                                       {
                                           "assets/shaders/postProcessing/pp.vert",
                                           "assets/shaders/postProcessing/edgeDetection.frag",
                                       });

    this->ppPipe.SetSize(glutil::GetWindowWidth(), glutil::GetWindowHeight());
    this->ppPipe.SetUseUboData(true);
    this->ppPipe.SetColorsEnabled(true);
    this->ppPipe.SetDepthAndStencilEnabled(true);
    this->ppPipe.SetColorBufferTextureTarget(GL_TEXTURE0);
    this->ppPipe.SetDepthAndStencilEnabled(true);
    this->ppPipe.SetDepthStencilBufferTextureTarget(GL_TEXTURE1);
    this->ppPipe.SetBindingTarget(0);
    this->ppPipe.Update();
    this->ppPipe.CreateGlObjects();
}

gui::DebugScreenBase::~DebugScreenBase()
{
    for (auto obj : this->objects)
        delete obj;

    this->objects.clear();
}

void gui::DebugScreenBase::Render()
{
    if (this->ppProg)
        this->ppPipe.StartRecording();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    this->scene.GetProgram(DEPTH_PROG)->Use();
    this->scene.Render();

    glDepthFunc(GL_EQUAL);

    if (this->debugProg)
        this->debugProg->Use();
    else
        this->scene.GetProgram(COLOR_PROG)->Use();

    this->scene.Render();

    if (this->ppProg)
    {
        this->ppProg->Use();
        this->ppPipe.Render();
    }
}

void gui::DebugScreenBase::SetGlState()
{
    glPolygonMode(GL_FRONT_AND_BACK, this->wireMode ? GL_LINE : GL_FILL);
}

void gui::DebugScreenBase::Update(double delta)
{
    this->cameraUpdater.Update(delta);

    if (glutil::WasKeyPressed(GLFW_KEY_Q))
        glutil::Quit();
    if (glutil::WasKeyPressed(GLFW_KEY_F2))
        this->debugProg = nullptr;
    if (glutil::WasKeyPressed(GLFW_KEY_F3))
        this->debugProg = this->scene.GetProgram(DEBUG_NRM_PROG);
    if (glutil::WasKeyPressed(GLFW_KEY_F4))
        this->debugProg = this->scene.GetProgram(DEBUG_TEX_PROG);
    if (glutil::WasKeyPressed(GLFW_KEY_F5))
    {
        this->wireMode = !this->wireMode;
    }

    if (glutil::WasKeyPressed(GLFW_KEY_P))
        this->animationPaused = !this->animationPaused;
    if (glutil::WasKeyPressed(GLFW_KEY_R))
        this->scene.ReloadAllShaders();
    if (glutil::WasButtonPressed(GLFW_MOUSE_BUTTON_1))
    {
        this->cameraUpdater.Enable();
        glutil::SetCursorGameMode(true);
        this->mouseCaptured = true;
    }
    if (glutil::WasButtonPressed(GLFW_MOUSE_BUTTON_2))
    {
        this->cameraUpdater.Disable();
        glutil::SetCursorGameMode(false);
        this->mouseCaptured = false;
    }

    if (!this->animationPaused)
        for (auto obj : this->objects)
            obj->Update(delta);

    if (glutil::WasWindowResized())
    {
        this->ppPipe.SetSize(glutil::GetWindowWidth(), glutil::GetWindowHeight());
        this->ppPipe.Update();
    }
}
