#include "GlScreens.hpp"
#include "DummyData.hpp"
#include "data/Io.hpp"
#include "glm/gtx/transform.hpp"
#include "data/Random.hpp"
#include "graphics/Color.hpp"

namespace
{
const std::string MainCam = "MainCam";
const std::string DepthProg = "Prog1";
const std::string ColorProg = "Prog2";

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
                                  objects()
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
                                           "assets/shaders/simple.vert",
                                           "assets/shaders/simple.frag",
                                       });

    this->scene.InitProgramFromSources(DepthProg,
                                       {
                                           "assets/shaders/simple.vert",
                                           "assets/shaders/simple.frag",
                                       });

    auto cubeTex = this->scene.GetTexture("CubeTex");
    cubeTex->SetMinFilterMode(GL_LINEAR_MIPMAP_LINEAR);
    cubeTex->SetMipmapsEnabled(true);
    cubeTex->LoadData("assets/textures/dummy/pebble.jpg");
    cubeTex->Bind(GL_TEXTURE0);

    auto coords = this->scene.GetObject("Coord");
    coords->SetGeometry(this->scene.GetMesh("CoordMesh"));
    coords->GetGeometry()->LoadFromBuffer(gui::models::CoordMesh());
    coords->SetModelMatrix(glm::scale(glm::vec3(5.f, 5.f, 5.f)));
    coords->SetBindingTarget(0);
    coords->CreateGlObjects();

    auto cubeMesh = this->scene.GetMesh("CubeMesh");
    gui::quadrics::Box(*cubeMesh);

    for (int i = 0; i < 30; i++)
    {
        auto obj = this->scene.GetObject(util::Format("Cube_%", i));
        obj->SetGeometry(cubeMesh);
        obj->SetBindingTarget(0);
        obj->CreateGlObjects();

        this->objects.push_back(new DummyObject(obj));
    }
}

gui::DummyScreen::~DummyScreen()
{
    for (auto obj : this->objects)
        delete obj;

    this->objects.clear();
}

void gui::DummyScreen::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);

    this->scene.GetProgram(DepthProg)->Use();
    this->scene.Render();

    glDepthFunc(GL_EQUAL);

    this->scene.GetProgram(ColorProg)->Use();
    this->scene.Render();
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

    if (glutil::IsKeyDown(GLFW_KEY_F5))
        camera->SetViewDirection(-camera->GetViewDirection());

    if (glutil::WasKeyPressed(GLFW_KEY_R))
    {
        this->scene.GetProgram(DepthProg)->ReloadAll();
        this->scene.GetProgram(ColorProg)->ReloadAll();
    }

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
    }

    camera->UpdateMatrices();
}
