#include "GlScreens.hpp"

#include "DummyData.hpp"
#include "data/Io.hpp"
#include "glm/gtx/transform.hpp"
#include "data/Random.hpp"
#include "graphics/Color.hpp"

namespace
{
struct PlanetInfo
{
    std::string name;
    std::string path;
    float radius;
    float size;
};
} // namespace

gui::PlanetScreen::PlanetScreen() : scene(),
                                    cameraUpdater()
{
    auto camera = this->scene.GetCamera("cam");
    camera->SetViewDirection(glm::vec3(0.f, 0.f, 1.f));
    camera->SetPosition(glm::vec3(0.f, 0.f, 0.f));
    camera->SetUp(glutil::AXIS_Y);
    camera->SetBindingTarget(1);
    camera->CreateGlObjects();

    this->scene.SetActiveCamera("cam");
    this->cameraUpdater.SetCamera(camera);

    glEnable(GL_DEPTH_TEST);

    this->scene.InitProgramFromSources("prog",
                                       {
                                           "assets/shaders/base/full.vert",
                                           "assets/shaders/vertex/simple.vert",
                                           "assets/shaders/base/color.frag",
                                           "assets/shaders/fragment/lightingPhong.frag",
                                           "assets/shaders/fragment/materialPropsSimple.frag",
                                           "assets/shaders/fragment/normalAttrib.frag",
                                           "assets/shaders/fragment/textureOnly.frag",
                                       });

    this->scene.InitProgramFromSources("sky",
                                       {
                                           "assets/shaders/base/full.vert",
                                           "assets/shaders/vertex/skybox.vert",
                                           "assets/shaders/base/color.frag",
                                           "assets/shaders/fragment/lightingNone.frag",
                                           "assets/shaders/fragment/materialPropsSimple.frag",
                                           "assets/shaders/fragment/normalNull.frag",
                                           "assets/shaders/fragment/albedoSkybox.frag",
                                       });

    auto lights = this->scene.GetLightSet("light");
    lights->SetBindingTarget(4);
    auto light = lights->Add();
    light.SetActive(true);
    light.SetAmbientFactor(0.3f);
    light.SetColor(glm::vec3(1.0f, 1.0f, 1.0f) * 0.75f);
    light.SetPosition(glm::vec3(0.f, 0.f, 0.f));
    light.SetType(glutil::LightType::Point);

    this->scene.SetActiveLightSet("light");

    std::vector<PlanetInfo> planetInfos = {

        {"sun", "assets/textures/planets/sun.jpg", 0.f, 0.2f},
        {"mercury", "assets/textures/planets/mercury.jpg", 1.f, 0.2f},
        {"venus", "assets/textures/planets/venusSurface.jpg", 2.f, 0.2f},
        {"earthDay", "assets/textures/planets/earth/day.jpg", 3.f, 0.2f},
        {"mars", "assets/textures/planets/mars.jpg", 4.f, 0.2f},
        {"jupiter", "assets/textures/planets/jupiter.jpg", 5.f, 0.2f},
        {"saturn", "assets/textures/planets/saturn.jpg", 6.f, 0.2f},
        {"uranus", "assets/textures/planets/uranus.jpg", 7.f, 0.2f},
        {"neptune", "assets/textures/planets/neptune.jpg", 8.f, 0.2f},
        {"moonyWorld", "assets/textures/planets/moonyWorld.png", 9.f, 0.2f},
        {"moon", "assets/textures/planets/moon.jpg", -1.f, 0.2f},
        {"venus2", "assets/textures/planets/venusAtmosphere.jpg", -2.f, 0.2f},
        {"wateryWorld", "assets/textures/planets/wateryWorld.png", -3.f, 0.2f},
        {"earthNight", "assets/textures/planets/earth/night.jpg", -4.f, 0.2f},
    };

    auto planetMesh = this->scene.GetMesh("UvMesh");
    gui::quadrics::UvSphere(32, 20, *planetMesh);

    util::Random rnd;

    for (int i = 0; i < planetInfos.size(); i++)
    {
        auto &info = planetInfos[i];

        auto texture = this->scene.GetTexture(info.name);
        texture->SetMipmapsEnabled(true);
        texture->SetMinFilterMode(GL_LINEAR_MIPMAP_LINEAR);
        texture->LoadData(info.path);

        auto material = this->scene.GetMaterial(info.name);
        material->SetAlbedo(glm::vec4(0.5f, 0.5f, 0.5f, 1.f));
        material->SetAlbedoMap(texture, GL_TEXTURE0);

        auto obj = this->scene.GetObject(info.name);
        obj->SetModelMatrix(glm::translate(glm::vec3(info.radius, 0.f, 0.f) * info.radius) *
                            glm::rotate(static_cast<float>(rnd.Next(0.0, 2 * M_PI)), glm::vec3(0, 1, 0)) *
                            glm::scale(glm::vec3(info.size, info.size, info.size)));
        obj->SetMaterial(material);
        obj->SetGeometry(planetMesh);
        obj->SetBindingTarget(2);
        obj->CreateGlObjects();

        this->objects.push_back(new PlanetObject(obj, info.radius));
    }

    this->scene.GetTexture("sky1")->LoadCubeMap("assets/textures/skyboxes/night/", ".png");
    this->scene.GetTexture("sky2")->LoadCubeMap("assets/textures/skyboxes/tropicalSunnyDay/", ".jpg");
    this->scene.GetTexture("sky3")->LoadCubeMap("assets/textures/skyboxes/lagoon/", ".tga");
    this->scene.GetTexture("sky4")->LoadCubeMap("assets/textures/skyboxes/spires/", ".tga");
    this->scene.GetTexture("sky5")->LoadCubeMap("assets/textures/skyboxes/thunder/", ".tga");
    this->scene.GetTexture("sky6")->LoadCubeMap("assets/textures/skyboxes/stars/", ".png");

    this->skyBox.SetProgram(this->scene.GetProgram("sky"));
    this->skyBox.SetTexture(this->scene.GetTexture("sky1"), GL_TEXTURE4);
}

gui::PlanetScreen::~PlanetScreen()
{
    for (auto obj : this->objects)
        delete obj;

    this->objects.clear();
}

void gui::PlanetScreen::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->scene.GetProgram("prog")->Use();
    this->scene.Render();

    this->skyBox.Render();
}

void gui::PlanetScreen::Update(double delta)
{
    for (auto &obj : this->objects)
        obj->Update(delta);

    this->cameraUpdater.Update(delta);

    if (glutil::WasKeyPressed(GLFW_KEY_Q))
        glutil::Quit();
    if (glutil::WasButtonPressed(GLFW_MOUSE_BUTTON_1))
    {
        this->cameraUpdater.Enable();
        glutil::SetCursorGameMode(true);
    }

    if (glutil::WasButtonPressed(GLFW_MOUSE_BUTTON_2))
    {
        this->cameraUpdater.Disable();
        glutil::SetCursorGameMode(false);
    }

    if (glutil::WasKeyPressed(GLFW_KEY_1))
        this->skyBox.SetTexture(this->scene.GetTexture("sky1"), GL_TEXTURE4);
    if (glutil::WasKeyPressed(GLFW_KEY_2))
        this->skyBox.SetTexture(this->scene.GetTexture("sky2"), GL_TEXTURE4);
    if (glutil::WasKeyPressed(GLFW_KEY_3))
        this->skyBox.SetTexture(this->scene.GetTexture("sky3"), GL_TEXTURE4);
    if (glutil::WasKeyPressed(GLFW_KEY_4))
        this->skyBox.SetTexture(this->scene.GetTexture("sky4"), GL_TEXTURE4);
    if (glutil::WasKeyPressed(GLFW_KEY_5))
        this->skyBox.SetTexture(this->scene.GetTexture("sky5"), GL_TEXTURE4);
    if (glutil::WasKeyPressed(GLFW_KEY_6))
        this->skyBox.SetTexture(this->scene.GetTexture("sky6"), GL_TEXTURE4);
}