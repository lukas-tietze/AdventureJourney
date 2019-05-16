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

glutil::Mesh *glutil::SceneObject::GetGeometry()
{
    return this->geometry;
}

void glutil::SceneObject::Render()
{
    if (this->geometry)
        this->geometry->Draw();
}