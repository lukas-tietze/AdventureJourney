#include "GlScreens.hpp"
#include "DummyData.hpp"
#include "data/Io.hpp"
#include "glm/gtx/transform.hpp"
#include "data/Random.hpp"

gui::DummyObjectScreen::DummyObjectScreen()
{
    this->camera.SetViewDirection(glm::vec3(-1.f, -1.f, -1.f));
    this->camera.SetPosition(glm::vec3(2.f, 2.f, 2.f));
    this->camera.SetUp(glutil::AXIS_Y);
    this->camera.SetBindingTarget(1);
    this->camera.CreateGlObjects();

    glEnable(GL_DEPTH_TEST);

    pId = glutil::CreateProgram("assets/shaders/passthrough.vs.glsl",
                                "assets/shaders/passthrough.fs.glsl");

    if (!pId)
        util::err.WriteLine("Failed to load program!");

    this->objects.push_back(new glutil::SceneObject(gui::models::CoordMesh()));
    this->objects.back()->SetModelMatrix(glm::scale(glm::vec3(5.f, 5.f, 5.f)));

    const auto &cubeMesh = gui::models::CubeMesh();
    auto cubeGeometry = new glutil::GeometryBuffer(cubeMesh);
    auto rnd = util::Random();

    for (int i = 0; i < 30; i++)
    {
        auto translateMat = glm::vec3(rnd.Next(-5.f, 5.f),
                                      rnd.Next(-5.f, 5.f),
                                      rnd.Next(-5.f, 5.f));

        auto scale = rnd.Next(0.1f, 0.5f);
        auto scaleMat = glm::vec3(scale, scale, scale);

        auto rotateAxis = glm::vec3(rnd.Next(0.0f, 1.0f),
                                    rnd.Next(0.0f, 1.0f),
                                    rnd.Next(0.0f, 1.0f));

        auto rotateDeg = rnd.Next(0.f, 360.f);

        this->objects.push_back(new glutil::SceneObject(cubeGeometry, cubeMesh));
        this->objects.back()->SetModelMatrix(glm::translate(translateMat) * glm::rotate(rotateDeg, rotateAxis) * glm::scale(scaleMat));
    }

    // this->objects.push_back(new glutil::SceneObject(gui::models::Coord3dMesh()));
    // this->objects.back()->SetModelMatrix(glm::translate(glm::vec3(-1.f, -1.f, 1.f)));

    for (auto object : this->objects)
    {
        object->SetBindingTarget(0);
        object->CreateGlObjects();
        glutil::ThrowOnGlError();
    }

    glutil::SetCursorGameMode(true);
}

gui::DummyObjectScreen::~DummyObjectScreen()
{
    for (auto object : this->objects)
    {
        object->DestroyGlObjects();
        delete object;
    }

    this->objects.clear();
    this->camera.DestroyGlObjects();
}

void gui::DummyObjectScreen::Render()
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
}

void gui::DummyObjectScreen::Update(double delta)
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

    // this->objects[0]->SetModelMatrix(glm::rotate(this->objects[0]->GetModelMatrix(), (float)delta, glutil::AXIS_X));
    // this->objects[0]->SetModelMatrix(glm::rotate(this->objects[0]->GetModelMatrix(), (float)delta, glutil::AXIS_Y));
    // this->objects[0]->SetModelMatrix(glm::rotate(this->objects[0]->GetModelMatrix(), (float)delta, glutil::AXIS_Z));

    this->camera.MoveBy(viewFlat * (float)(delta * x) +
                        this->camera.GetUp() * (float)(delta * y) +
                        viewCross * (float)(delta * z));
    this->camera.Rotate(glutil::GetMouseDeltaX() * delta * -10.f, glutil::AXIS_Y);
    this->camera.Rotate(glutil::GetMouseDeltaY() * delta * -10.f, viewCross);

    if (glutil::WasWindowResized())
    {
        this->camera.SetAspectRation(glutil::GetAspectRatio());
    }

    this->camera.UpdateMatrices();
}
