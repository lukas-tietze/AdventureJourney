#pragma once

#include <string>
#include <vector>
#include <map>
#include "glm/glm.hpp"

namespace glutil
{
template <class TData>
class StaticUboOwner
{
  private:
    int ubo;
    int bindingTarget;
    bool dirty;

  protected:
    TData data;

  public:
    StaticUboOwner();

    void CreateGlObjects();
    void DestroyGlObjects();
    void Bind() const;
    void SetBindingTarget(int);
    void Upload() const;
    void SetDirty();
};

#include "gui/src/Objects/StaticUboOwner.inl"

template <class TData>
class DynamicUboOwner
{
  private:
    int ubo;
    int bindingTarget;
    bool dirty;
    int bufferSize;

  protected:
    std::vector<TData> data;

  public:
    DynamicUboOwner();

    void CreateGlObjects();
    void DestroyGlObjects();
    void Bind() const;
    void SetBindingTarget(int);
    void Upload() const;
    void SetDirty();
};

#include "gui/src/Objects/DynamicUboOwner.inl"

class GeometryBufferAttribute
{
  private:
    int index;
    int type;
    int count;
    int offset;
    bool normalized;

  public:
    GeometryBufferAttribute();
    GeometryBufferAttribute(int index, int count, int type, bool normalized, int offset);

    int GetIndex() const;
    int GetType() const;
    int GetCount() const;
    int GetOffset() const;
    bool IsNormalized() const;
};

class Mesh
{
  private:
    int vertexCount;
    int indexCount;
    int vertexSize;
    int indexSize;
    std::vector<GeometryBufferAttribute> attributes;
    void *vertices;
    void *indices;

  public:
    Mesh();

    bool LoadFromJson(const std::string &path);
    bool LoadFromCg2vd(const std::string &path);
    bool LoadFromData(int vertexCount, int vertexSize, void *vertices, int indexCount, int indexSize, void *indices, std::vector<GeometryBufferAttribute> attributes);

    //  bool IsCompatibleToBuffer();

    int GetVertexCount() const;
    int GetIndexCount() const;
    int GetVertexSize() const;
    int GetIndexSize() const;
    int GetVertexDataSize() const;
    int GetIndexDataSize() const;
    const void *GetVertexData() const;
    const void *GetIndexData() const;
    const std::vector<GeometryBufferAttribute> &GetAttributes() const;
};

class Geometry
{
  private:
    GLuint vao;
    GLuint vbo;
    GLuint ibo;

  public:
    Geometry(const Mesh &);
    Geometry(const std::vector<Mesh *> &);
    Geometry(const Mesh *, size_t count);

    ~Geometry();

    void Bind();
};

struct SceneObjectUboData
{
    glm::mat4 modelMatrix;
};

class SceneObject : StaticUboOwner<SceneObjectUboData>
{
  private:
    int bufferOffset;
    int indexCount;
    int offset;
    int drawMode;
    int indexType;
    Geometry *geometry;
    bool geometryManaged;

  public:
    SceneObject(Geometry *data, int indexCount, int offset, int drawMode, int indexType);
    SceneObject(const Mesh &, int indexType = GL_UNSIGNED_SHORT, int drawMode = GL_TRIANGLES);
    ~SceneObject();

    const glm::mat4 &GetModelMatrix() const;

    void Render();
};

class Camera
{
  private:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 direction;
    float fov;
    float near;
    float far;
    float aspectRation;

    glm::mat4 viewMat;
    bool viewDirty;
    glm::mat4 projectionMat;
    bool projectionDirty;
    glm::mat4 viewProjectionMat;

  public:
    Camera();

    void SetPosition(glm::vec3 const &pos);
    void SetUp(glm::vec3 const &up);
    void SetViewDirection(glm::vec3 const &direction);

    void MoveBy(glm::vec3 const &dist);
    void Rotate(float degrees, glm::vec3 const &axis);

    void SetFov(float fov);
    void SetNear(float near);
    void SetFar(float far);
    void SetRange(float near, float far);
    void SetAspectRation(int w, int h);
    void SetAspectRation(float ratio);

    void UpdateMatrices();

    const glm::mat4 &GetViewProjectionMatrix() const;
    const glm::mat4 &GetViewProjectionMatrix();
    const glm::mat4 &GetViewMatrix() const;
    const glm::mat4 &GetViewMatrix();
    const glm::mat4 &GetProjectionMatrix() const;
    const glm::mat4 &GetProjectionMatrix();
    const glm::vec3 &GetPosition() const;
    const glm::vec3 &GetUp() const;
    const glm::vec3 &GetViewDirection() const;
    float GetFov() const;
    float GetNear() const;
    float GetFar() const;
    float GetAspectRation() const;
};

struct SceneUboData
{
    glm::mat4 viewMat;
    glm::mat4 inverseViewMat;
    glm::mat4 projectionMat;
    glm::mat4 inverseProjectionMat;
    glm::mat4 normalMat;
};

class Scene : public StaticUboOwner<SceneUboData>
{
  private:
    std::map<int, Geometry *> geometry;
    Camera camera;

  public:
    bool AddGeometry();

    void Render();
};
} // namespace glutil
