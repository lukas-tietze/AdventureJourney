#pragma once

#include <vector>

#include "GlUtils.hpp"
#include "Objects.hpp"
#include "glm/glm.hpp"

namespace gui
{
class DummyObject : public glutil::SceneObject
{
private:
    glm::vec3 axis;
    float rotation;
    glm::vec3 basePos;
    float pos;
    float max;
    float speed;
    float scale;

public:
    DummyObject(const glutil::Mesh &);

    void Step(double delta);
};

class DummyScreen : public glutil::Screen
{
private:
    std::vector<gui::DummyObject *> objects;
    glutil::SceneObject *axis;

    glutil::Shader vertexShader;
    glutil::Shader fragmentShader;
    glutil::Program program;

    glutil::Camera camera;

    bool mouseCaptured;

public:
    DummyScreen();
    ~DummyScreen();

    void Render();
    void Update(double);
};
} // namespace gui
