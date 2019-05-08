#include "GlScreens.hpp"
#include "DummyData.hpp"
#include "data/Io.hpp"
#include "glm/gtx/transform.hpp"
#include "data/Random.hpp"

gui::DummyScreen::DummyScreen()
{
    this->camera.SetViewDirection(glm::vec3(-1.f, -1.f, -1.f));
    this->camera.SetPosition(glm::vec3(7.f, 7.f, 7.f));
    this->camera.SetUp(glutil::AXIS_Y);
    this->camera.SetBindingTarget(1);
    this->camera.CreateGlObjects();

    glEnable(GL_DEPTH_TEST);

    this->vertexShader.LoadFrom("assets/shaders/passthrough.vs.glsl", GL_VERTEX_SHADER);
    this->fragmentShader.LoadFrom("assets/shaders/passthrough.fs.glsl", GL_FRAGMENT_SHADER);
    this->program.AttachShader(&this->vertexShader);
    this->program.AttachShader(&this->fragmentShader);
    this->program.Link();

    this->axis = new glutil::SceneObject(gui::models::CoordMesh());
    this->axis->SetModelMatrix(glm::scale(glm::vec3(5.f, 5.f, 5.f)));

    auto cubeMesh = gui::quadrics::Box();

    auto cubeGeometry = new glutil::GeometryBuffer(cubeMesh);
    auto rnd = util::Random();

    for (int i = 0; i < 30; i++)
        this->objects.push_back(new gui::DummyObject(cubeGeometry, cubeMesh));

    for (auto object : this->objects)
    {
        object->SetBindingTarget(0);
        object->CreateGlObjects();
    }

    this->axis->SetBindingTarget(0);
    this->axis->CreateGlObjects();
}

gui::DummyScreen::~DummyScreen()
{
    for (auto object : this->objects)
    {
        object->DestroyGlObjects();
        delete object;
    }

    this->axis->DestroyGlObjects();
    delete this->axis;

    this->objects.clear();
    this->camera.DestroyGlObjects();
}

void gui::DummyScreen::Render()
{
    this->program.Use();

    this->camera.Upload(true);
    this->camera.Bind();

    for (auto object : this->objects)
    {
        object->Upload(true);
        object->Bind();
        object->Render();
    }

    this->axis->Upload();
    this->axis->Bind();
    this->axis->Render();
}

void gui::DummyScreen::Update(double delta)
{
    int x = 0;
    int y = 0;
    int z = 0;

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
        this->camera.SetViewDirection(-this->camera.GetViewDirection());

    if (glutil::IsKeyDown(GLFW_KEY_F5))
        this->program.ReloadAll();

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

    auto viewFlat = this->camera.GetViewDirection();
    viewFlat.y = 0;

    auto viewCross = glm::cross(viewFlat, this->camera.GetUp());
    viewCross.y = 0;

    for (int i = 0; i < this->objects.size(); i++)
    {
        this->objects[i]->Step(delta);
    }

    this->camera.MoveBy(viewFlat * static_cast<float>(delta * x) +
                        this->camera.GetUp() * static_cast<float>(delta * y) +
                        viewCross * static_cast<float>(delta * z));

    if (this->mouseCaptured)
    {
        this->camera.Rotate(static_cast<float>(glutil::GetMouseDeltaX() * -1), glutil::AXIS_Y);
        this->camera.Rotate(static_cast<float>(glutil::GetMouseDeltaY() * -1), viewCross);
    }

    if (glutil::WasWindowResized())
    {
        this->camera.SetAspectRation(glutil::GetAspectRatio());
    }

    this->camera.UpdateMatrices();
}
