#include "GlScreens.hpp"
#include "DummyData.hpp"
#include "glm/gtx/transform.hpp"

gui::DummyObjectScreen::DummyObjectScreen()
{
    this->camera.SetViewDirection(glm::vec3(-1.f, -1.f, -1.f));
    this->camera.SetPosition(glm::vec3(2.f, 2.f, 2.f));
    this->camera.SetUp(glutil::AXIS_Y);

    glEnable(GL_DEPTH_TEST);

    pId = glutil::CreateProgram("assets/shaders/example.vs.glsl",
                                "assets/shaders/example.fs.glsl");

    glutil::Mesh meshes[2];
    meshes[0].LoadFromData(8, sizeof(gui::models::Vertex_XYZ_RGB), gui::models::cubeData,
                           36, sizeof(GLubyte), gui::models::cubeIndices,
                           {glutil::GeometryBufferAttribute(0, 3, GL_FLOAT, GL_FALSE, offsetof(gui::models::Vertex_XYZ_RGB, position)),
                            glutil::GeometryBufferAttribute(1, 3, GL_UNSIGNED_BYTE, GL_FALSE, offsetof(gui::models::Vertex_XYZ_RGB, color))});

    this->objects.push_back(new glutil::SceneObject(meshes[0], GL_UNSIGNED_BYTE));

    meshes[1].LoadFromData(6, sizeof(gui::models::Vertex_XYZ_RGB), gui::models::coordData,
                           6, sizeof(GLubyte), gui::models::coordIndices,
                           {glutil::GeometryBufferAttribute(0, 3, GL_FLOAT, GL_FALSE, offsetof(gui::models::Vertex_XYZ_RGB, position)),
                            glutil::GeometryBufferAttribute(1, 3, GL_UNSIGNED_BYTE, GL_FALSE, offsetof(gui::models::Vertex_XYZ_RGB, color))});

    this->objects.push_back(new glutil::SceneObject(meshes[1], GL_UNSIGNED_BYTE, GL_LINES));
}

gui::DummyObjectScreen::~DummyObjectScreen()
{
    for (auto object : this->objects)
        delete object;

    this->objects.clear();
}

void gui::DummyObjectScreen::Render()
{
    auto vp = this->camera.GetViewProjectionMatrix();

    glUseProgram(pId);
    glUniformMatrix4fv(0, 1, GL_FALSE, &(vp[0][0]));
    this->objects[0]->Render();

    auto mvp = vp * glm::scale(glm::vec3(5.f, 5.f, 5.f));
    glUniformMatrix4fv(0, 1, GL_FALSE, &(mvp[0][0]));
    this->objects[1]->Render();

    // for (auto object : this->objects)
    //     object->Render();
}

void gui::DummyObjectScreen::Update(double delta)
{
    int x = 0;
    int y = 0;
    int z = 0;
    int r = 0;

    if (glutil::IsKeyDown(GLFW_KEY_ESCAPE))
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
    if (glutil::IsKeyDown(GLFW_KEY_Q))
        r--;
    if (glutil::IsKeyDown(GLFW_KEY_E))
        r++;

    auto viewFlat = this->camera.GetViewDirection();
    viewFlat.y = 0;

    auto viewCross = glm::cross(this->camera.GetUp(), viewFlat);
    viewCross.y = 0;

    this->camera.MoveBy(viewFlat * (float)(delta * x) +
                        this->camera.GetUp() * (float)(delta * y) +
                        viewCross * (float)(delta * z));
    this->camera.Rotate(glm::degrees(r * delta), this->camera.GetUp());
    this->camera.UpdateMatrices();
}
