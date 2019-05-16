#include "Objects.hpp"
#include "GlUtils.hpp"

glutil::Scene::Scene() : objects(),
                         materials(),
                         programs(),
                         textures(),
                         shaders(),
                         cameras(),
                         meshs(),
                         lightSets(),
                         activeCamera(nullptr),
                         activeLightSet(nullptr)
{
}

glutil::Scene::~Scene()
{
    this->DeleteAll(this->objects);
    this->DeleteAll(this->materials);
    this->DeleteAll(this->programs);
    this->DeleteAll(this->textures);
    this->DeleteAll(this->shaders);
    this->DeleteAll(this->cameras);
    this->DeleteAll(this->meshs);
    this->DeleteAll(this->lightSets);
    this->DeleteAll(this->fonts);
}

glutil::SceneObject *glutil::Scene::GetObject(const resourceId_t &id)
{
    return this->FindOrCreateItem(this->objects, id);
}

glutil::Material *glutil::Scene::GetMaterial(const resourceId_t &id)
{
    return this->FindOrCreateItem(this->materials, id);
}

glutil::Program *glutil::Scene::GetProgram(const resourceId_t &id)
{
    return this->FindOrCreateItem(this->programs, id);
}

glutil::Texture *glutil::Scene::GetTexture(const resourceId_t &id)
{
    return this->FindOrCreateItem(this->textures, id);
}

glutil::Shader *glutil::Scene::GetShader(const resourceId_t &id)
{
    return this->FindOrCreateItem(this->shaders, id);
}

glutil::Camera *glutil::Scene::GetCamera(const resourceId_t &id)
{
    return this->FindOrCreateItem(this->cameras, id);
}

glutil::Mesh *glutil::Scene::GetMesh(const resourceId_t &id)
{
    return this->FindOrCreateItem(this->meshs, id);
}

glutil::LightSet *glutil::Scene::GetLightSet(const resourceId_t &id)
{
    return this->FindOrCreateItem(this->lightSets, id);
}

glutil::BitMapFont *glutil::Scene::GetFont(const resourceId_t &id)
{
    return this->FindOrCreateItem(this->fonts, id);
}

const glutil::SceneObject *glutil::Scene::GetObject(const resourceId_t &id) const
{
    return this->FindItemOrNull(this->objects, id);
}

const glutil::Material *glutil::Scene::GetMaterial(const resourceId_t &id) const
{
    return this->FindItemOrNull(this->materials, id);
}

const glutil::Program *glutil::Scene::GetProgram(const resourceId_t &id) const
{
    return this->FindItemOrNull(this->programs, id);
}

const glutil::Texture *glutil::Scene::GetTexture(const resourceId_t &id) const
{
    return this->FindItemOrNull(this->textures, id);
}

const glutil::Shader *glutil::Scene::GetShader(const resourceId_t &id) const
{
    return this->FindItemOrNull(this->shaders, id);
}

const glutil::Camera *glutil::Scene::GetCamera(const resourceId_t &id) const
{
    return this->FindItemOrNull(this->cameras, id);
}

const glutil::Mesh *glutil::Scene::GetMesh(const resourceId_t &id) const
{
    return this->FindItemOrNull(this->meshs, id);
}

const glutil::LightSet *glutil::Scene::GetLightSet(const resourceId_t &id) const
{
    return this->FindItemOrNull(this->lightSets, id);
}

const glutil::BitMapFont *glutil::Scene::GetFont(const resourceId_t &id) const
{
    return this->FindItemOrNull(this->fonts, id);
}

bool glutil::Scene::RemoveObject(const resourceId_t &id)
{
    return this->DeleteItem(this->objects, id);
}

bool glutil::Scene::RemoveMaterial(const resourceId_t &id)
{
    return this->DeleteItem(this->materials, id);
}

bool glutil::Scene::RemoveProgram(const resourceId_t &id)
{
    return this->DeleteItem(this->programs, id);
}

bool glutil::Scene::RemoveTexture(const resourceId_t &id)
{
    return this->DeleteItem(this->textures, id);
}

bool glutil::Scene::RemoveShader(const resourceId_t &id)
{
    return this->DeleteItem(this->shaders, id);
}

bool glutil::Scene::RemoveCamera(const resourceId_t &id)
{
    return this->DeleteItem(this->cameras, id);
}

bool glutil::Scene::RemoveMesh(const resourceId_t &id)
{
    return this->DeleteItem(this->meshs, id);
}

bool glutil::Scene::RemoveLightSet(const resourceId_t &id)
{
    return this->DeleteItem(this->lightSets, id);
}

bool glutil::Scene::RemoveFont(const resourceId_t &id)
{
    return this->DeleteItem(this->fonts, id);
}

void glutil::Scene::ReloadAllShaders()
{
    for (auto kvp : this->shaders)
        kvp.second->Reload();

    for (auto kvp : this->programs)
        kvp.second->Link();
}

void glutil::Scene::SetActiveCamera(const resourceId_t &id)
{
    auto kvp = this->cameras.find(id);
    this->activeCamera = kvp != this->cameras.end() ? kvp->second : nullptr;
}

void glutil::Scene::SetActiveLightSet(const resourceId_t &id)
{
    auto kvp = this->lightSets.find(id);
    this->activeLightSet = kvp != this->lightSets.end() ? kvp->second : nullptr;
}

glutil::Shader *glutil::Scene::InitShader(const resourceId_t &id, const std::string &sourcePath)
{
    auto shader = this->GetShader(id);

    shader->LoadFrom(sourcePath);

    return shader;
}

glutil::Program *glutil::Scene::InitProgram(const resourceId_t &id, const std::initializer_list<std::string> &shaderNames)
{
    auto program = this->GetProgram(id);

    for (const auto &shaderName : shaderNames)
        program->Attach(this->GetShader(shaderName));

    program->Link();

    return program;
}

glutil::Program *glutil::Scene::InitProgramFromSources(const resourceId_t &id, const std::initializer_list<std::string> &sources)
{
    auto program = this->GetProgram(id);

    for (const auto &source : sources)
    {
        auto shader = this->GetShader(source);

        shader->LoadFrom(source);
        program->Attach(shader);
    }

    program->Link();

    return program;
}

void glutil::Scene::Render()
{
    if (this->activeCamera)
    {
        this->activeCamera->Bind();
        this->activeCamera->Upload();
    }

    if (this->activeLightSet)
    {
        this->activeLightSet->Bind();
        this->activeLightSet->Upload();
    }

    for (auto &obj : this->objects)
    {
        obj.second->Bind();
        obj.second->Upload();
        obj.second->Render();
    }
}

void glutil::Scene::Update(double delta)
{
    for (auto &obj : this->objects)
    {
        // obj.second->Update(delta);
    }
}
