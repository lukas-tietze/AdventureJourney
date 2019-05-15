#include "GlScreens.hpp"
#include "DummyData.hpp"
#include "data/Io.hpp"
#include "glm/gtx/transform.hpp"
#include "data/Random.hpp"
#include "graphics/Color.hpp"

namespace
{
const std::string MainCam = "MainCam";
const std::string MainLight = "MainLight";
const std::string DepthProg = "Prog1";
const std::string ColorProg = "Prog2";
const std::string PixelationProg = "PPpix";
const std::string NoPpProg = "PPoff";
const std::string BlurProg = "PPblur";
const std::string DepthBlurProg = "PPdepthBlur";
const std::string EdgeDetectionProg = "PPedge";

struct TextureBuilder
{
    uint32_t operator()(float x, float y) const
    {
        return util::Color(x * (1 - y), x * (1 - y), x * y * (1 - x) * (1 - y)).Value();
    }
};

struct NormalMapBuilder
{
    uint32_t operator()(float x, float y) const
    {
        return util::Color(x * (1 - y), x * (1 - y), x * y * (1 - x) * (1 - y)).Value();
    }
};
} // namespace

gui::DummyScreen::DummyScreen() : scene(),
                                  objects(),
                                  mouseCaptured(false),
                                  animationPaused(false),
                                  wireMode(false)
{
    auto camera = this->scene.GetCamera(MainCam);
    camera->SetViewDirection(glm::vec3(-1.f, -1.f, -1.f));
    camera->SetPosition(glm::vec3(7.f, 7.f, 7.f));
    camera->SetUp(glutil::AXIS_Y);
    camera->SetBindingTarget(1);
    camera->CreateGlObjects();
    this->scene.SetActiveCamera(MainCam);

    glEnable(GL_DEPTH_TEST);

    this->scene.InitProgramFromSources(ColorProg,
                                       {
                                           "assets/shaders/base/full.vert",
                                           "assets/shaders/vertex/simple.vert",
                                           "assets/shaders/base/color.frag",
                                           "assets/shaders/fragment/lightingPhong.frag",
                                           "assets/shaders/fragment/materialPropsSimple.frag",
                                           "assets/shaders/fragment/normalAttrib.frag",
                                           "assets/shaders/fragment/textureOnly.frag",
                                       });

    this->scene.InitProgramFromSources(DepthProg,
                                       {
                                           "assets/shaders/base/positionOnly.vert",
                                           "assets/shaders/vertex/simple.vert",
                                           "assets/shaders/base/depth.frag",
                                           "assets/shaders/fragment/textureOnly.frag",
                                       });

    this->ppProg = this->scene.InitProgramFromSources(NoPpProg,
                                                      {
                                                          "assets/shaders/postProcessing/pp.vert",
                                                          "assets/shaders/postProcessing/noPp.frag",
                                                      });

    this->scene.InitProgramFromSources(PixelationProg,
                                       {
                                           "assets/shaders/postProcessing/pp.vert",
                                           "assets/shaders/postProcessing/pixelate.frag",
                                       });

    this->scene.InitProgramFromSources(BlurProg,
                                       {
                                           "assets/shaders/postProcessing/pp.vert",
                                           "assets/shaders/postProcessing/blur.frag",
                                       });

    this->scene.InitProgramFromSources(DepthBlurProg,
                                       {
                                           "assets/shaders/postProcessing/pp.vert",
                                           "assets/shaders/postProcessing/depthBlur.frag",
                                       });

    this->scene.InitProgramFromSources(EdgeDetectionProg,
                                       {
                                           "assets/shaders/postProcessing/pp.vert",
                                           "assets/shaders/postProcessing/edgeDetection.frag",
                                       });

    auto lights = this->scene.GetLightSet(MainLight);
    lights->SetBindingTarget(4);
    auto light = lights->Add();
    light.SetActive(true);
    light.SetAmbientFactor(0.3);
    light.SetColor(glm::vec3(0.3f, 0.7f, 0.9f));
    light.SetPosition(glm::vec3(0.f, 0.f, 0.f));
    light.SetType(glutil::LightType::Point);
    this->scene.SetActiveLightSet(MainLight);

    auto cubeTex = this->scene.GetTexture("CubeTex");
    cubeTex->SetMinFilterMode(GL_LINEAR_MIPMAP_LINEAR);
    cubeTex->SetMipmapsEnabled(true);
    cubeTex->LoadData("assets/textures/dummy/grass.jpg");
    cubeTex->Bind(GL_TEXTURE0);

    auto icoMesh = this->scene.GetMesh("IcoMesh");
    gui::quadrics::IcoSphere(2, *icoMesh);

    auto diskMesh = this->scene.GetMesh("DiskMesh");
    gui::quadrics::Disk(16, 2, *diskMesh);

    auto cubeMesh = this->scene.GetMesh("CubeMesh");
    gui::quadrics::Box(*cubeMesh);

    auto cylinderMesh = this->scene.GetMesh("CylinderMesh");
    gui::quadrics::Cylinder(16, 1, *cylinderMesh);

    util::Random rnd;

    for (int i = 0; i < 30; i++)
    {
        auto obj = this->scene.GetObject(util::Format("Cube_%", i));

        switch (rnd.Next(0, 4))
        {
        case 0:
            obj->SetGeometry(cubeMesh);
            break;
        case 1:
            obj->SetGeometry(icoMesh);
            break;
        case 2:
            obj->SetGeometry(cylinderMesh);
            break;
        case 3:
            obj->SetGeometry(diskMesh);
            break;
        }

        obj->SetBindingTarget(2);
        obj->CreateGlObjects();

        this->objects.push_back(new DummyObject(obj));
    }

    this->ppPipe.SetSize(glutil::GetWindowWidth(), glutil::GetWindowHeight());
    this->ppPipe.SetUseUboData(true);
    this->ppPipe.SetColorsEnabled(true);
    this->ppPipe.SetColorBufferTextureTarget(GL_TEXTURE0);
    this->ppPipe.SetDepthAndStencilEnabled(true);
    this->ppPipe.SetDepthStencilBufferTextureTarget(GL_TEXTURE1);
    this->ppPipe.SetBindingTarget(0);
    this->ppPipe.Update();
}

gui::DummyScreen::~DummyScreen()
{
    for (auto obj : this->objects)
        delete obj;

    this->objects.clear();
}

void gui::DummyScreen::Render()
{
    this->ppPipe.StartRecording();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    this->scene.GetProgram(DepthProg)->Use();
    this->scene.Render();

    glDepthFunc(GL_EQUAL);

    this->scene.GetProgram(ColorProg)->Use();
    this->scene.Render();

    this->ppProg->Use();
    this->ppPipe.Render();
}

void gui::DummyScreen::Update(double delta)
{
    int x = 0;
    int y = 0;
    int z = 0;

    auto camera = this->scene.GetCamera(MainCam);

    if (glutil::IsKeyDown(GLFW_KEY_ESCAPE) || glutil::IsKeyDown(GLFW_KEY_Q))
        glutil::Quit();
    if (glutil::IsKeyDown(GLFW_KEY_W))
        x++;
    if (glutil::IsKeyDown(GLFW_KEY_S))
        x--;
    if (glutil::IsKeyDown(GLFW_KEY_D))
        z++;
    if (glutil::IsKeyDown(GLFW_KEY_A))
        z--;
    if (glutil::IsKeyDown(GLFW_KEY_SPACE))
        y++;
    if (glutil::IsKeyDown(GLFW_KEY_LEFT_SHIFT))
        y--;
    if (glutil::WasKeyPressed(GLFW_KEY_F1))
    {
        this->wireMode = !this->wireMode;

        glPolygonMode(GL_FRONT_AND_BACK, this->wireMode ? GL_LINE : GL_FILL);
    }
    if (glutil::WasKeyPressed(GLFW_KEY_F2))
        this->ppProg = this->scene.GetProgram(NoPpProg);
    if (glutil::WasKeyPressed(GLFW_KEY_F3))
        this->ppProg = this->scene.GetProgram(PixelationProg);
    if (glutil::WasKeyPressed(GLFW_KEY_F4))
        this->ppProg = this->scene.GetProgram(BlurProg);
    if (glutil::WasKeyPressed(GLFW_KEY_F5))
        this->ppProg = this->scene.GetProgram(DepthBlurProg);
    if (glutil::WasKeyPressed(GLFW_KEY_F6))
        this->ppProg = this->scene.GetProgram(EdgeDetectionProg);

    if (glutil::WasKeyPressed(GLFW_KEY_P))
        this->animationPaused = !this->animationPaused;
    if (glutil::IsKeyDown(GLFW_KEY_C))
        camera->SetViewDirection(-camera->GetViewDirection());
    if (glutil::WasKeyPressed(GLFW_KEY_R))
        this->scene.ReloadAllShaders();
    if (glutil::WasButtonPressed(GLFW_MOUSE_BUTTON_1))
    {
        glutil::SetCursorGameMode(true);
        this->mouseCaptured = true;
    }
    if (glutil::WasButtonPressed(GLFW_MOUSE_BUTTON_2))
    {
        glutil::SetCursorGameMode(false);
        this->mouseCaptured = false;
    }

    auto viewFlat = camera->GetViewDirection();
    viewFlat.y = 0;

    auto viewCross = glm::cross(viewFlat, camera->GetUp());
    viewCross.y = 0;

    if (!this->animationPaused)
        for (auto obj : this->objects)
            obj->Step(delta);

    camera->MoveBy(viewFlat * static_cast<float>(delta * x) +
                   camera->GetUp() * static_cast<float>(delta * y) +
                   viewCross * static_cast<float>(delta * z));

    if (this->mouseCaptured)
    {
        camera->Rotate(static_cast<float>(glutil::GetMouseDeltaX() * -1), glutil::AXIS_Y);
        camera->Rotate(static_cast<float>(glutil::GetMouseDeltaY() * -1), viewCross);
    }

    if (glutil::WasWindowResized())
    {
        camera->SetAspectRation(glutil::GetAspectRatio());
        this->ppPipe.SetSize(glutil::GetWindowWidth(), glutil::GetWindowHeight());
        this->ppPipe.Update();
    }

    camera->UpdateMatrices();
}
