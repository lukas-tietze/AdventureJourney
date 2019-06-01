#pragma once

#include <vector>

#include "GlUtils.hpp"
#include "Objects.hpp"
#include "glm/glm.hpp"

namespace gui
{
class IDummyObject
{
public:
    virtual ~IDummyObject();

    virtual void Step(double delta) = 0;
};

class DummyObject : public IDummyObject
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

class DummyLightSource : public IDummyObject
{
private:
    glutil::SceneObject *sceneObject;
    glutil::LightSet::Light light;
    float pos;
    float speed;
    float radius;

public:
    DummyLightSource(glutil::SceneObject *sceneObject, glutil::LightSet::Light light, float pos, float speed, float radius);

    void Step(double delta);
};

class DummyScreen : public glutil::Screen
{
private:
    glutil::Scene scene;
    glutil::CameraUpdater cameraUpdater;

    bool mouseCaptured;
    bool animationPaused;
    bool wireMode;
    bool cullMode;

    std::vector<IDummyObject *> objects;
    glutil::Program *ppProg;
    glutil::Program *debugProg;

    glutil::PostProcessingPipeline ppPipe;

public:
    DummyScreen();
    ~DummyScreen();

    void Render();
    void Update(double);
};

class PlanetScreen : public glutil::Screen
{
private:
    glutil::Scene scene;
    glutil::CameraUpdater cameraUpdater;

public:
    PlanetScreen();
};
} // namespace gui
