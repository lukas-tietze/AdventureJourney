#pragma once

#include <vector>
#include <tuple>

#include "GlUtils.hpp"
#include "Objects.hpp"
#include "glm/glm.hpp"

namespace gui
{
class IDebugObject
{
public:
    virtual ~IDebugObject();

    virtual void Update(double delta) = 0;
};

class DebugScreenBase : public glutil::Screen
{
private:
    bool mouseCaptured;
    bool animationPaused;
    bool wireMode;
    bool cullMode;

    std::vector<std::tuple<int, const char *>> postProcessProgs;
    std::vector<std::tuple<int, const char *>> renderProgs;

    std::string postProcessProg;
    std::string renderProg;

    void SetGlState();

protected:
    glutil::Scene scene;
    glutil::CameraUpdater cameraUpdater;
    glutil::PostProcessingPipeline ppPipe;
    glutil::SkyBox skybox;

    std::vector<IDebugObject *> objects;

public:
    DebugScreenBase();
    ~DebugScreenBase();

    void Render();
    void Update(double);

    virtual void BeforeRender() = 0;
    virtual void AfterRender() = 0;
    virtual void BeforeUpdate() = 0;
    virtual void AfterUpdate() = 0;
};

class DummyScreen : public DebugScreenBase
{
public:
    DummyScreen();
    ~DummyScreen();

    virtual void BeforeRender();
    virtual void AfterRender();
    virtual void BeforeUpdate();
    virtual void AfterUpdate();
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

    void Upate(double delta);
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

    void Update(double delta);
};

class PlanetObject : public IDebugObject
{
private:
    glutil::SceneObject *object;
    float radius;
    float arc;
    float speed;
    float size;

public:
    PlanetObject(glutil::SceneObject *, float radius);

    void Update(double delta);
};

class PlanetScreen : public DebugScreenBase
{
public:
    PlanetScreen();
    ~PlanetScreen();

    virtual void BeforeRender();
    virtual void AfterRender();
    virtual void BeforeUpdate();
    virtual void AfterUpdate();
};
} // namespace gui
