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

    virtual void Update(double delta) = 0;
};

class DebugScreenBase : public glutil::Screen
{
private:
    bool mouseCaptured;
    bool animationPaused;
    bool wireMode;
    bool cullMode;

    std::unordered_map<int, std::string> progs;

    void SetGlState();

protected:
    glutil::Scene scene;
    glutil::CameraUpdater cameraUpdater;

    std::vector<IDebugObject *> objects;
    std::string renderProg;
    std::string postProcessorProg;

    glutil::PostProcessingPipeline ppPipe;

    virtual void BeforeRender();
    virtual void AfterRender();
    virtual void BeforeUpdate();
    virtual void AfterUpdate();
    virtual void LoadShaders();
    virtual void LoadScene();

public:
    DebugScreenBase();
    ~DebugScreenBase();

    void Render();
    void Update(double);
};

class DummyScreen
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
private:
    glutil::Scene scene;
    glutil::CameraUpdater cameraUpdater;
    std::vector<PlanetObject *> objects;
    glutil::SkyBox skyBox;
    glutil::DeferredRenderingPipeline drp;

public:
    PlanetScreen();
    ~PlanetScreen();

    void Render();
    void Update(double);
};
} // namespace gui
