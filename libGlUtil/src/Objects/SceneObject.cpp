#include "Objects.hpp"
#include "data/Io.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

glutil::SceneObject::SceneObject() : geometry(nullptr)
{
}

glutil::SceneObject::SceneObject(Mesh *mesh) : geometry(mesh)
{
}

glutil::SceneObject::SceneObject(const SceneObject &copy) : geometry(copy.geometry)
{
}

glutil::SceneObject::SceneObject(SceneObject &&transferFrom) : geometry(transferFrom.geometry)
{
    transferFrom.geometry = nullptr;
}

glutil::SceneObject::~SceneObject()
{
}

const glm::mat4 &glutil::SceneObject::GetModelMatrix() const
{
    return this->data.modelMatrix;
}

void glutil::SceneObject::SetModelMatrix(const glm::mat4 &mat)
{
    this->data.modelMatrix = mat;
    this->data.normalMatrix = glm::inverseTranspose(mat);
    this->SetDirty();
}

void glutil::SceneObject::SetGeometry(glutil::Mesh *geometry)
{
    this->geometry = geometry;
}

void glutil::SceneObject::SetProgram(glutil::Program *program)
{
    this->program = program;
}

void glutil::SceneObject::SetMaterial(glutil::Material *material)
{
    this->material = material;
}

glutil::Mesh *glutil::SceneObject::GetGeometry()
{
    return this->geometry;
}

glutil::Program *glutil::SceneObject::GetProgram()
{
    return this->program;
}

glutil::Material *glutil::SceneObject::GetMaterial()
{
    return this->material;
}

void glutil::SceneObject::Render()
{
    if (this->program && this->material && this->geometry)
    {
        this->program->Use();
        this->material->Use();
        this->Bind();
        this->Upload();
        this->geometry->Draw();
    }
}

void glutil::SceneObject::RenderDepthPass()
{
    if (this->geometry)
    {
        this->Bind();
        this->Upload();
        this->geometry->Draw();
    }
}