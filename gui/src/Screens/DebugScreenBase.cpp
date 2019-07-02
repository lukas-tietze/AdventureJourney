#include "GlScreens.hpp"
#include "DummyData.hpp"
#include "data/Io.hpp"
#include "glm/gtx/transform.hpp"
#include "data/Random.hpp"
#include "graphics/Color.hpp"

namespace
{
constexpr char MAIN_CAM[] = "MAIN_CAM";

constexpr char RP_DEPTH[] = "rp_depth";
constexpr char RP_DEFERRED[] = "rp_deferred";

constexpr char LP_FULL[] = "lp_color";
constexpr char LP_DEBUG_COLOR[] = "lp_color";
constexpr char LP_DEBUG_NRM[] = "lp_debug_nrm";
constexpr char LP_DEBUG_ALBEDO[] = "lp_debug_albedo";
constexpr char LP_DEBUG_MATERIAL[] = "lp_debug_material";
constexpr char LP_DEBUG_DEPTH[] = "lp_debug_depth";

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
                                          renderProg(RP_DEFERRED),
                                          postProcessProg(PP_OFF),
                                          lightingProg(LP_DEBUG_ALBEDO)
{
    auto camera = this->scene.GetCamera(MAIN_CAM);
    camera->SetViewDirection(glm::vec3(1.f, 0.f, 0.f));
    camera->SetPosition(glm::vec3(-2.f, 3.f, 0.f));
    camera->SetUp(glutil::AXIS_Y);
    camera->SetBindingTarget(1);
    camera->CreateGlObjects();

    this->scene.SetActiveCamera(MAIN_CAM);
    this->cameraUpdater.SetCamera(camera);

    this->lightingProgs.push_back(std::make_tuple(GLFW_KEY_1, LP_FULL));
    this->lightingProgs.push_back(std::make_tuple(GLFW_KEY_2, LP_DEBUG_COLOR));
    this->lightingProgs.push_back(std::make_tuple(GLFW_KEY_3, LP_DEBUG_NRM));
    this->lightingProgs.push_back(std::make_tuple(GLFW_KEY_4, LP_DEBUG_ALBEDO));
    this->lightingProgs.push_back(std::make_tuple(GLFW_KEY_5, LP_DEBUG_MATERIAL));
    this->lightingProgs.push_back(std::make_tuple(GLFW_KEY_6, LP_DEBUG_DEPTH));

    this->scene.InitProgramFromSources(this->renderProg,
                                       {
                                           "assets/shaders/base/deferredIn.vert",
                                           "assets/shaders/base/deferredIn.frag",
                                           "assets/shaders/fragment/normal/attrib.frag",
                                           "assets/shaders/fragment/albedo/textureOnly.frag",
                                           "assets/shaders/fragment/materialProps/null.frag",
                                       });

    this->scene.InitProgramFromSources(LP_DEBUG_ALBEDO,
                                       {
                                           "assets/shaders/base/deferredOut.vert",
                                           "assets/shaders/base/deferredOut.frag",
                                           "assets/shaders/fragment/lighting/phong.frag",
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
    this->ppPipe.SetBindingTarget(0);
    this->ppPipe.SetColorsEnabled(true);
    this->ppPipe.SetDepthAndStencilEnabled(true);
    this->ppPipe.SetColorBufferTextureTarget(GL_TEXTURE0);
    this->ppPipe.SetDepthStencilBufferTextureTarget(GL_TEXTURE1);
    this->ppPipe.Update();
    this->ppPipe.CreateGlObjects();

    this->drPipe.SetSize(glutil::GetWindowWidth(), glutil::GetWindowHeight());
    this->drPipe.SetUseUboData(false);
    this->drPipe.Update();
    this->drPipe.CreateGlObjects();

    this->InitShaders();
    this->InitModels();
    this->InitCameras();
    this->InitLights();
    this->InitScene();
    this->InitPipelines();
}

gui::DebugScreenBase::~DebugScreenBase()
{
    for (auto obj : this->objects)
        delete obj;

    this->objects.clear();
}

void gui::DebugScreenBase::InitShaders()
{
}

void gui::DebugScreenBase::InitModels()
{
}

void gui::DebugScreenBase::InitCameras()
{
}

void gui::DebugScreenBase::InitLights()
{
}

void gui::DebugScreenBase::InitScene()
{
}

void gui::DebugScreenBase::InitPipelines()
{
}

void gui::DebugScreenBase::Render()
{
    glutil::PushDebugGroup("Render loop");

    glutil::PushDebugGroup("Before Render");
    this->BeforeRender();

    glutil::NextDebugGroup("Set Gl State");
    this->SetGlState();

    auto pp = this->scene.GetProgram(this->postProcessProg);
    auto rp = this->scene.GetProgram(this->renderProg);
    auto lp = this->scene.GetProgram(this->lightingProg);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glutil::NextDebugGroup("dr record");
    this->drPipe.StartRecording();
    rp->Use();
    this->scene.Render();

    glutil::NextDebugGroup("dr render");
    lp->Use();

    this->drPipe.Render();

    glutil::NextDebugGroup("After Render");
    this->AfterRender();

    glutil::PopDebugGroup();
    glutil::PopDebugGroup();
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
        for (const auto kvp : this->lightingProgs)
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
        this->drPipe.SetSize(glutil::GetWindowWidth(), glutil::GetWindowHeight());
        this->drPipe.Update();
    }

    this->AfterUpdate();
}