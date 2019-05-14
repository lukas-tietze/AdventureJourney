#pragma once

#include <vector>

#include "GlUtils.hpp"
#include "Objects.hpp"
#include "glm/glm.hpp"

namespace gui
{
class DummyObject
{
private:
    glutil::SceneObject *sceneObject;

    glm::vec3 axis;
    float rotation;
    glm::vec3 basePos;
    float pos;
    float max;
    float speed;
    float scale;

public:
    DummyObject(glutil::SceneObject *);

    void Step(double delta);
};

class DummyScreen : public glutil::Screen
{
private:
    glutil::Scene scene;

    bool mouseCaptured;
    bool animationPaused;
    bool wireMode;

    std::vector<DummyObject *> objects;
    glutil::Program *ppProg;

    glutil::PostProcessingPipeLine ppPipe;

public:
    DummyScreen();
    ~DummyScreen();

    void Render();
    void Update(double);
};
} // namespace gui
