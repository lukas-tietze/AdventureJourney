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

    pId = glutil::CreateProgram("assets/shaders/passthrough.vs.glsl",
                                "assets/shaders/passthrough.fs.glsl");

    if (!pId)
        util::err.WriteLine("Failed to load program!");

    this->axis = new glutil::SceneObject(gui::models::CoordMesh());
    this->axis->SetModelMatrix(glm::scale(glm::vec3(5.f, 5.f, 5.f)));

    auto cubeMesh = gui::models::CubeMesh();
    // auto cubeMesh = gui::quadrics::Box();
    cubeMesh = gui::quadrics::Box();
    auto cubeGeometry = new glutil::GeometryBuffer(cubeMesh);
    auto rnd = util::Random();

    for (int i = 0; i < 1; i++)
        this->objects.push_back(new gui::DummyObject(cubeGeometry, cubeMesh));

    // this->objects.push_back(new glutil::SceneObject(gui::models::Coord3dMesh()));
    // this->objects.back()->SetModelMatrix(glm::translate(glm::vec3(-1.f, -1.f, 1.f)));

    for (auto object : this->objects)
    {
        object->SetBindingTarget(0);
        object->CreateGlObjects();
        glutil::ThrowOnGlError();
    }

    this->axis->SetBindingTarget(0);
    this->axis->CreateGlObjects();
    glutil::ThrowOnGlError();

    glutil::SetCursorGameMode(true);
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
    glUseProgram(pId);

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

    auto viewFlat = this->camera.GetViewDirection();
    viewFlat.y = 0;

    auto viewCross = glm::cross(viewFlat, this->camera.GetUp());
    viewCross.y = 0;

    for (int i = 0; i < this->objects.size(); i++)
    {
        // this->objects[i]->Step(delta);
    }

    this->camera.MoveBy(viewFlat * static_cast<float>(delta * x) +
                        this->camera.GetUp() * static_cast<float>(delta * y) +
                        viewCross * static_cast<float>(delta * z));
    this->camera.Rotate(glutil::GetMouseDeltaX() * static_cast<float>(delta) * -10.f, glutil::AXIS_Y);
    this->camera.Rotate(glutil::GetMouseDeltaY() * static_cast<float>(delta) * -10.f, viewCross);

    if (glutil::WasWindowResized())
    {
        this->camera.SetAspectRation(glutil::GetAspectRatio());
    }

    this->camera.UpdateMatrices();
}
