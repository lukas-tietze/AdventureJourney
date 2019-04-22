#include "Objects.hpp"
#include "data/Io.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

glutil::SceneObject::SceneObject(Geometry *geometry, int indexCount, int offset, int drawMode, int indexType) : indexCount(indexCount),
                                                                                                                offset(offset),
                                                                                                                drawMode(drawMode),
                                                                                                                indexType(indexType),
                                                                                                                geometry(geometry),
                                                                                                                geometryManaged(false)
{
    util::dbg.WriteLine("Created Scene Object: indexCount: %, offset: %, drawMode %, indexType: %",
                        indexCount,
                        offset,
                        drawMode,
                        indexType);
}

glutil::SceneObject::SceneObject(const Mesh &mesh, int indexType, int drawMode) : indexCount(mesh.GetIndexCount()),
                                                                                  offset(0),
                                                                                  drawMode(drawMode),
                                                                                  indexType(indexType),
                                                                                  geometry(new Geometry(mesh)),
                                                                                  geometryManaged(true)
{
    util::dbg.WriteLine("Created Scene Object: indexCount: %, offset: %, drawMode %, indexType: %",
                        indexCount,
                        offset,
                        drawMode,
                        indexType);
}

glutil::SceneObject::~SceneObject()
{
    if (this->geometryManaged)
        delete this->geometry;
}

const glm::mat4 &glutil::SceneObject::GetModelMatrix() const
{
    return this->data.modelMatrix;
}

void glutil::SceneObject::SetModelMatrix(const glm::mat4 &mat)
{
    this->data.modelMatrix = mat;
    this->data.normalMatrix = glm::inverseTranspose(glm::mat3(mat));
    this->SetDirty();
}

void glutil::SceneObject::Render()
{
    this->geometry->Bind();
    glDrawElements(this->drawMode, this->indexCount, this->indexType, (void *)this->offset);
}