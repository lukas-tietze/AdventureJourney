#pragma once

#include <vector>

#include "GlUtils.hpp"
#include "Objects.hpp"
#include "glm/glm.hpp"

namespace gui
{
class IDebugObject
{
public:
    virtual ~IDebugObject();

    virtual void Step(double delta) = 0;
};

class DebugScreenBase : public glutil::Screen
{
protected:
    glutil::Scene scene;
    glutil::CameraUpdater cameraUpdater;

    bool mouseCaptured;
    bool animationPaused;
    bool wireMode;
    bool cullMode;

    std::vector<IDebugObject *> objects;
    glutil::Program *ppProg;
    glutil::Program *debugProg;

    glutil::PostProcessingPipeline ppPipe;

protected:
    virtual void BeforeRender();
    virtual void AfterRender();
    virtual void BeforeUpdate();
    virtual void AfterUpdate();

public:
    DebugScreenBase();
    ~DebugScreenBase();

    void Render();
    void Update(double);
};

class DummyScreen : public DebugScreenBase
{
public:
    DummyScreen();
    ~DummyScreen();

    void Render();
    void Update(double);
};

class DummyObject : public IDebugObject
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

class DummyLightSource : public IDebugObject
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

class PlanetObject
{
private:
    glutil::SceneObject *object;

public:
    PlanetObject(glutil::SceneObject *);
};

class PlanetScreen : public glutil::Screen
{
private:
    glutil::Scene scene;
    glutil::CameraUpdater cameraUpdater;
    std::vector<PlanetObject> objects;
    glutil::SkyBox skyBox;

public:
    PlanetScreen();

    void Render();
    void Update(double);
};
} // namespace gui
