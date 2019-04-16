#pragma once

#include "GlUtils.hpp"
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

    void OnShow();
    void OnHide();
};
} // namespace gui
