#include "Objects.hpp"

glutil::Scene::Scene() : objects(),
                         materials(),
                         programs(),
                         textures(),
                         shaders(),
                         cameras(),
                         meshs()
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

void glutil::Scene::SetActiveCamera(const resourceId_t &id)
{
    auto kvp = this->cameras.find(id);
    this->activeCamera = kvp != this->cameras.end() ? kvp->second : nullptr;
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
