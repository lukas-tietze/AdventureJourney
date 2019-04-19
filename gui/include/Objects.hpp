#pragma once

#include <string>
#include <vector>
#include <map>
#include "glm/glm.hpp"

namespace gui
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
    int length;
    int offset;
    bool normalized;

  public:
    int GetIndex() const;
    int GetType() const;
    int GetLength() const;
    int GetOffset() const;
    bool IsNormalized() const;
};

class SceneObjectUboData
{
    glm::mat4 modelMatrix;
};

class SceneObject : StaticUboOwner<SceneObjectUboData>
{
  private:
    int indexCount;
    int offset;
    int drawMode;
    int indexType;

  public:
    SceneObject(const Geometry &);

    void Render();
};

class Geometry
{
  private:
    int vao;
    int vbo;
    int ibo;
};

class Mesh
{
  private:
    int vertexCount;
    int indexCount;
    int vertexDataSize;
    int indexDataSize;
    std::vector<GeometryBufferAttribute> attributes;
    void *vertices;
    void *indices;

  public:
    Mesh();

    bool LoadFromJson(const std::string &path);
    bool LoadFromCg2vd(const std::string &path);
    bool LoadFromData(int vertexCount, int vertexDataSize, void *vertices, int indexCount, int indexDataSize, void *indices, std::vector<GeometryBufferAttribute> attributes);

    bool IsCompatibleToBuffer();

    int GetVertexCount() const;
    int GetIndexCount() const;
    int GetVertexDataSize() const;
    int GetIndexDataSize() const;
    const std::vector<GeometryBufferAttribute> &GetAttributes() const;
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

    void Flush(glm::mat4 &projectionBuf, glm::mat4 &viewBuf);
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
} // namespace gui
