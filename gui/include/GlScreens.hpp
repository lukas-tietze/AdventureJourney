#pragma once

#include <vector>

#include "GlUtils.hpp"
#include "Objects.hpp"
#include "glm/glm.hpp"

namespace gui
{
class DummyScreen : public glutil::Screen
{
  private:
    GLuint vbo;
    GLuint ibo;
    GLuint vao;
    GLuint pId;

    glm::vec3 eyePos;
    glm::mat4 modelViewProjectionMat;
    float rotation;

  public:
    DummyScreen();
    ~DummyScreen();

    void Render();
    void Update(double);
};

class DummyObjectScreen : public glutil::Screen
{
  private:
    std::vector<glutil::SceneObject *> objects;

    GLuint pId;

    glutil::Camera camera;

  public:
    DummyObjectScreen();
    ~DummyObjectScreen();

    void Render();
    void Update(double);
};
} // namespace gui
