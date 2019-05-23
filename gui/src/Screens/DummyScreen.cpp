#include "GlScreens.hpp"
#include "DummyData.hpp"
#include "data/Io.hpp"
#include "glm/gtx/transform.hpp"
#include "data/Random.hpp"
#include "graphics/Color.hpp"

namespace
{
constexpr char MAIN_CAM[] = "MAIN_CAM";
constexpr char MAIN_LIGHT[] = "MAIN_LIGHT";
constexpr char DEPTH_PROG[] = "PrgDepth";
constexpr char COLOR_PROG[] = "PrgColorFull";
constexpr char DEBUG_TEX_PROG[] = "PrgTexDebug";
constexpr char DEBUG_NRM_PROG[] = "PrgNrmDebug";
constexpr char PIXEL_PROG[] = "PPpix";
constexpr char BLUR_PROG[] = "PPblur";
constexpr char DEPTH_BLUR_PROG[] = "PPdepthBlur";
constexpr char EDGE_PROG[] = "PPedge";

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
                                  wireMode(false),
                                  cullMode(false),
                                  debugProg(nullptr),
                                  ppProg(nullptr)
{
    auto camera = this->scene.GetCamera(MAIN_CAM);
    camera->SetViewDirection(glm::vec3(-1.f, -1.f, -1.f));
    camera->SetPosition(glm::vec3(1.f, 2.f, 1.f));
    camera->SetUp(glutil::AXIS_Y);
    camera->SetBindingTarget(1);
    camera->CreateGlObjects();
    this->scene.SetActiveCamera(MAIN_CAM);

    glEnable(GL_DEPTH_TEST);

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

    auto lights = this->scene.GetLightSet(MAIN_LIGHT);
    lights->SetBindingTarget(4);
    auto light = lights->Add();
    light.SetActive(true);
    light.SetAmbientFactor(0.3f);
    light.SetColor(glm::vec3(1.0f, 1.0f, 1.0f) * 0.75f);
    light.SetPosition(glm::vec3(0.f, 1.f, 0.f));
    light.SetType(glutil::LightType::Point);
    this->scene.SetActiveLightSet(MAIN_LIGHT);

    auto grassTex = this->scene.GetTexture("Grass");
    grassTex->SetMinFilterMode(GL_LINEAR_MIPMAP_LINEAR);
    grassTex->SetMipmapsEnabled(true);
    grassTex->LoadData("assets/textures/grass.png");

    auto pebbleTex = this->scene.GetTexture("Pebble");
    pebbleTex->SetMinFilterMode(GL_LINEAR_MIPMAP_LINEAR);
    pebbleTex->SetMipmapsEnabled(true);
    pebbleTex->LoadData("assets/textures/pebble.png");

    auto gridTex = this->scene.GetTexture("Grid");
    gridTex->SetMinFilterMode(GL_LINEAR_MIPMAP_LINEAR);
    gridTex->SetMipmapsEnabled(true);
    gridTex->LoadData("assets/textures/CubeGrid.png");

    auto numGridTex = this->scene.GetTexture("NumGrid");
    numGridTex->SetMinFilterMode(GL_LINEAR_MIPMAP_LINEAR);
    numGridTex->SetMipmapsEnabled(true);
    numGridTex->LoadData("assets/textures/Numbered Grid.png");

    auto grassMaterial = this->scene.GetMaterial("Grass");
    grassMaterial->SetAlbedo(glm::vec4(0.3f, 0.8f, 0.5f, 1.f));
    grassMaterial->SetAlbedoMap(grassTex, GL_TEXTURE0);

    auto pebbleMaterial = this->scene.GetMaterial("Pebble");
    pebbleMaterial->SetAlbedo(glm::vec4(0.3f, 0.3f, 0.3f, 1.f));
    pebbleMaterial->SetAlbedoMap(pebbleTex, GL_TEXTURE0);

    auto gridMaterial = this->scene.GetMaterial("Grid");
    gridMaterial->SetAlbedo(glm::vec4(0.3f, 0.3f, 0.3f, 1.f));
    gridMaterial->SetAlbedoMap(gridTex, GL_TEXTURE0);

    auto numGridMaterial = this->scene.GetMaterial("NumGrid");
    numGridMaterial->SetAlbedo(glm::vec4(0.3f, 0.3f, 0.3f, 1.f));
    numGridMaterial->SetAlbedoMap(numGridTex, GL_TEXTURE0);

    auto testMaterial = numGridMaterial;

    auto floorMesh = this->scene.GetMesh("Floor");
    gui::quadrics::Quad(*floorMesh);

    auto icoMesh = this->scene.GetMesh("IcoMesh");
    gui::quadrics::IcoSphere(3, *icoMesh);

    auto uvMesh = this->scene.GetMesh("UvMesh");
    gui::quadrics::UvSphere(32, 20, *uvMesh);

    auto diskMesh = this->scene.GetMesh("DiskMesh");
    gui::quadrics::Disk(32, 1, *diskMesh);

    auto cubeMesh = this->scene.GetMesh("CubeMesh");
    gui::quadrics::Box(*cubeMesh);

    auto cylinderMesh = this->scene.GetMesh("CylinderMesh");
    gui::quadrics::Cylinder(32, 1, *cylinderMesh);

    auto coneMesh = this->scene.GetMesh("ConeMesh");
    gui::quadrics::Cone(32, 3, *coneMesh);

    auto floorObj = this->scene.GetObject("floor");
    floorObj->SetGeometry(floorMesh);
    floorObj->SetModelMatrix(glm::scale(glm::vec3(5, 5, 5)));
    floorObj->SetBindingTarget(2);
    floorObj->SetMaterial(pebbleMaterial);
    floorObj->CreateGlObjects();

    auto lamp = this->scene.GetObject("lamp");
    lamp->SetGeometry(icoMesh);
    lamp->SetModelMatrix(glm::translate(glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(0.1, 0.1, 0.1)));
    lamp->SetBindingTarget(2);
    lamp->SetMaterial(grassMaterial);
    lamp->CreateGlObjects();

    auto ico = this->scene.GetObject("Ico");
    ico->SetGeometry(icoMesh);

    auto uv = this->scene.GetObject("Uv");
    uv->SetGeometry(uvMesh);

    auto disk = this->scene.GetObject("Disk");
    disk->SetGeometry(diskMesh);

    auto cube = this->scene.GetObject("Cube");
    cube->SetGeometry(cubeMesh);

    auto cylinder = this->scene.GetObject("Cylinder");
    cylinder->SetGeometry(cylinderMesh);

    auto cone = this->scene.GetObject("Cone");
    cone->SetGeometry(coneMesh);

    std::vector<glutil::SceneObject *> objects = {
        cylinder,
        cone,
        cube,
        disk,
        ico,
        uv,
    };

    for (size_t i = 0; i < objects.size(); i++)
    {
        auto obj = objects[i];

        obj->SetModelMatrix(glm::translate(glm::vec3(1.f, 1.f, static_cast<float>(objects.size()) / 2.f - static_cast<float>(i))) * glm::scale(glm::vec3(0.3f, 0.3f, 0.3f)));
        obj->SetMaterial(testMaterial);
        obj->SetBindingTarget(2);
        obj->CreateGlObjects();
    }

    this->ppPipe.SetSize(glutil::GetWindowWidth(), glutil::GetWindowHeight());
    this->ppPipe.SetUseUboData(true);
    this->ppPipe.SetColorsEnabled(true);
    this->ppPipe.SetColorBufferTextureTarget(GL_TEXTURE0);
    this->ppPipe.SetDepthAndStencilEnabled(true);
    this->ppPipe.SetDepthStencilBufferTextureTarget(GL_TEXTURE1);
    this->ppPipe.SetBindingTarget(0);
    this->ppPipe.Update();
    this->ppPipe.CreateGlObjects();
}

gui::DummyScreen::~DummyScreen()
{
    for (auto obj : this->objects)
        delete obj;

    this->objects.clear();
}

void gui::DummyScreen::Render()
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

void gui::DummyScreen::Update(double delta)
{
    int x = 0;
    int y = 0;
    int z = 0;

    auto camera = this->scene.GetCamera(MAIN_CAM);

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
    if (glutil::WasKeyPressed(GLFW_KEY_F2))
        this->debugProg = nullptr;
    if (glutil::WasKeyPressed(GLFW_KEY_F3))
        this->debugProg = this->scene.GetProgram(DEBUG_NRM_PROG);
    if (glutil::WasKeyPressed(GLFW_KEY_F4))
        this->debugProg = this->scene.GetProgram(DEBUG_TEX_PROG);
    if (glutil::WasKeyPressed(GLFW_KEY_F5))
    {
        this->wireMode = !this->wireMode;

        glPolygonMode(GL_FRONT_AND_BACK, this->wireMode ? GL_LINE : GL_FILL);
    }

    if (glutil::WasKeyPressed(GLFW_KEY_1))
        this->ppProg = nullptr;
    if (glutil::WasKeyPressed(GLFW_KEY_2))
        this->ppProg = this->scene.GetProgram(PIXEL_PROG);
    if (glutil::WasKeyPressed(GLFW_KEY_3))
        this->ppProg = this->scene.GetProgram(BLUR_PROG);
    if (glutil::WasKeyPressed(GLFW_KEY_4))
        this->ppProg = this->scene.GetProgram(DEPTH_BLUR_PROG);
    if (glutil::WasKeyPressed(GLFW_KEY_5))
        this->ppProg = this->scene.GetProgram(EDGE_PROG);
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
