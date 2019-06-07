#include "GlScreens.hpp"
#include "DummyData.hpp"
#include "data/Io.hpp"
#include "glm/gtx/transform.hpp"
#include "data/Random.hpp"
#include "graphics/Color.hpp"

namespace
{
constexpr char MAIN_CAM[] = "MAIN_CAM";

constexpr char PR_DEPTH[] = "pr_depth";

constexpr char RP_COLOR[] = "pr_color";
constexpr char RP_DEBUG_TEX[] = "pr_debug_tex";
constexpr char RP_DEBUG_NRM[] = "pr_debug_nrm";

constexpr char PP_OFF[] = "pp_off";
constexpr char PP_PIXELATE[] = "pp_pixelate";
constexpr char PP_BLUR[] = "pp_blur";
constexpr char PP_DEPTH_BLUR[] = "pp_depthBlur";
constexpr char PP_EDGE[] = "pp_edge";

constexpr int KEY_CHANGE_RP = GLFW_KEY_LEFT_ALT;
constexpr int KEY_CHANGE_PPP = GLFW_KEY_LEFT_CONTROL;
constexpr int KEY_RELOAD_SHADERS = GLFW_KEY_R;
constexpr int KEY_EXIT = GLFW_KEY_Q;
constexpr int KEY_WIRE_MODE = GLFW_KEY_F1;
constexpr int KEY_CULL_MODE = GLFW_KEY_F2;
constexpr int KEY_PAUSE = GLFW_KEY_P;
} // namespace

gui::DebugScreenBase::DebugScreenBase() : scene(),
                                          objects(),
                                          mouseCaptured(false),
                                          animationPaused(false),
                                          wireMode(false),
                                          cullMode(false),
                                          renderProg(RP_COLOR),
                                          postProcessProg(PP_OFF)
{
    auto camera = this->scene.GetCamera(MAIN_CAM);
    camera->SetViewDirection(glm::vec3(1.f, 0.f, 0.f));
    camera->SetPosition(glm::vec3(0.f, 0.f, 0.f));
    camera->SetUp(glutil::AXIS_Y);
    camera->SetBindingTarget(1);
    camera->CreateGlObjects();

    this->scene.SetActiveCamera(MAIN_CAM);
    this->cameraUpdater.SetCamera(camera);

    this->renderProgs.push_back(std::make_tuple(GLFW_KEY_1, RP_COLOR));
    this->renderProgs.push_back(std::make_tuple(GLFW_KEY_2, RP_DEBUG_TEX));
    this->renderProgs.push_back(std::make_tuple(GLFW_KEY_3, RP_DEBUG_NRM));

    this->scene.InitProgramFromSources(RP_COLOR,
                                       {
                                           "assets/shaders/base/full.vert",
                                           "assets/shaders/vertex/simple.vert",
                                           "assets/shaders/base/color.frag",
                                           "assets/shaders/fragment/lightingPhong.frag",
                                           "assets/shaders/fragment/materialPropsSimple.frag",
                                           "assets/shaders/fragment/normalAttrib.frag",
                                           "assets/shaders/fragment/textureOnly.frag",
                                       });

    this->scene.InitProgramFromSources(RP_DEBUG_TEX,
                                       {
                                           "assets/shaders/base/full.vert",
                                           "assets/shaders/vertex/simple.vert",
                                           "assets/shaders/base/color.frag",
                                           "assets/shaders/fragment/lightingDebugTexCoord.frag",
                                           "assets/shaders/fragment/materialPropsSimple.frag",
                                           "assets/shaders/fragment/normalAttrib.frag",
                                           "assets/shaders/fragment/textureOnly.frag",
                                       });

    this->scene.InitProgramFromSources(RP_DEBUG_NRM,
                                       {
                                           "assets/shaders/base/full.vert",
                                           "assets/shaders/vertex/simple.vert",
                                           "assets/shaders/base/color.frag",
                                           "assets/shaders/fragment/lightingDebugNrm.frag",
                                           "assets/shaders/fragment/materialPropsSimple.frag",
                                           "assets/shaders/fragment/normalAttrib.frag",
                                           "assets/shaders/fragment/textureOnly.frag",
                                       });

    this->scene.InitProgramFromSources(PR_DEPTH,
                                       {
                                           "assets/shaders/base/positionOnly.vert",
                                           "assets/shaders/vertex/simple.vert",
                                           "assets/shaders/base/depth.frag",
                                           "assets/shaders/fragment/textureOnly.frag",
                                       });

    this->postProcessProgs.push_back(std::make_tuple(GLFW_KEY_1, PP_PIXELATE));
    this->postProcessProgs.push_back(std::make_tuple(GLFW_KEY_2, PP_BLUR));
    this->postProcessProgs.push_back(std::make_tuple(GLFW_KEY_3, PP_DEPTH_BLUR));
    this->postProcessProgs.push_back(std::make_tuple(GLFW_KEY_4, PP_EDGE));

    this->scene.InitProgramFromSources(PP_OFF,
                                       {
                                           "assets/shaders/postProcessing/pp.vert",
                                           "assets/shaders/postProcessing/noPp.frag",
                                       });

    this->scene.InitProgramFromSources(PP_PIXELATE,
                                       {
                                           "assets/shaders/postProcessing/pp.vert",
                                           "assets/shaders/postProcessing/pixelate.frag",
                                       });

    this->scene.InitProgramFromSources(PP_BLUR,
                                       {
                                           "assets/shaders/postProcessing/pp.vert",
                                           "assets/shaders/postProcessing/blur.frag",
                                       });

    this->scene.InitProgramFromSources(PP_DEPTH_BLUR,
                                       {
                                           "assets/shaders/postProcessing/pp.vert",
                                           "assets/shaders/postProcessing/depthBlur.frag",
                                       });

    this->scene.InitProgramFromSources(PP_EDGE,
                                       {
                                           "assets/shaders/postProcessing/pp.vert",
                                           "assets/shaders/postProcessing/edgeDetection.frag",
                                       });

    this->ppPipe.SetSize(glutil::GetWindowWidth(), glutil::GetWindowHeight());
    this->ppPipe.SetUseUboData(true);
    this->ppPipe.SetColorsEnabled(true);
    this->ppPipe.SetDepthAndStencilEnabled(true);
    this->ppPipe.SetColorBufferTextureTarget(GL_TEXTURE0);
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
    this->BeforeRender();

    this->SetGlState();

    auto pp = this->scene.GetProgram(this->postProcessProg);
    auto rp = this->scene.GetProgram(this->renderProg);
    auto dp = this->scene.GetProgram(PR_DEPTH);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);

    dp->Use();
    this->scene.Render();

    // this->ppPipe.StartRecording();

    glDepthFunc(GL_EQUAL);

    rp->Use();
    this->scene.Render();

    // pp->Use();
    // this->ppPipe.Render();

    this->AfterRender();
}

void gui::DebugScreenBase::SetGlState()
{
    glPolygonMode(GL_FRONT_AND_BACK, this->wireMode ? GL_LINE : GL_FILL);
    glEnable(GL_DEPTH_TEST);

    if (this->cullMode)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }
}

void gui::DebugScreenBase::Update(double delta)
{
    this->BeforeUpdate();

    this->cameraUpdater.Update(delta);

    if (glutil::WasKeyPressed(KEY_EXIT))
        glutil::Quit();

    if (glutil::WasKeyPressed(KEY_WIRE_MODE))
        this->wireMode = !this->wireMode;

    if (glutil::WasKeyPressed(KEY_CULL_MODE))
        this->cullMode = !this->cullMode;

    if (glutil::WasKeyPressed(KEY_PAUSE))
        this->animationPaused = !this->animationPaused;

    if (glutil::WasKeyPressed(KEY_RELOAD_SHADERS))
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

    if (glutil::IsKeyDown(KEY_CHANGE_PPP))
    {
        for (const auto kvp : this->postProcessProgs)
        {
            if (glutil::WasKeyPressed(std::get<0>(kvp)))
            {
                this->postProcessProg = std::get<1>(kvp);
                break;
            };
        }
    }
    else if (glutil::IsKeyDown(KEY_CHANGE_RP))
    {
        for (const auto kvp : this->renderProgs)
        {
            if (glutil::WasKeyPressed(std::get<0>(kvp)))
            {
                this->renderProg = std::get<1>(kvp);
                break;
            };
        }
    }

    if (!this->animationPaused)
        for (auto obj : this->objects)
            obj->Update(delta);

    if (glutil::WasWindowResized())
    {
        this->ppPipe.SetSize(glutil::GetWindowWidth(), glutil::GetWindowHeight());
        this->ppPipe.Update();
    }

    this->AfterUpdate();
}