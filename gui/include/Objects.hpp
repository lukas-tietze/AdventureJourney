#pragma once

#include <string>
#include <vector>
#include <map>
#include "glad/glad.h"
#include "glm/glm.hpp"

namespace glutil
{
template <class TData>
class StaticUboOwner
{
  private:
    GLuint ubo;
    GLuint bindingTarget;
    bool dirty;

  protected:
    TData data;

  public:
    StaticUboOwner();

    void CreateGlObjects();
    void DestroyGlObjects();
    void Bind() const;
    void SetBindingTarget(int);
    void Upload(bool force = false);
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
    void Upload(bool force = false);
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
    int vertexSize;
    void *vertices;
    int indexCount;
    int indexSize;
    int indexType;
    void *indices;
    std::vector<GeometryBufferAttribute> attributes;
    int drawMode;
    bool dataManaged;

    int CalculateIndexSize(int);

    void CopyFrom(const Mesh &);
    void TransferFrom(Mesh &);

  public:
    Mesh();
    Mesh(const Mesh &);
    Mesh(Mesh &&);
    ~Mesh();

    bool LoadFromJson(const std::string &path);
    bool LoadFromCg2vd(const std::string &path);
    bool LoadFromData(int vertexCount, int vertexSize, void *vertices,
                      int indexCount, int indexType, void *indices,
                      std::vector<GeometryBufferAttribute> attributes,
                      int drawMode, bool managaData = false);

    int GetVertexCount() const;
    int GetVertexSize() const;
    int GetVertexDataSize() const;
    const void *GetVertexData() const;
    int GetIndexCount() const;
    int GetIndexSize() const;
    int GetIndexType() const;
    int GetIndexDataSize() const;
    int GetDrawMode() const;
    const void *GetIndexData() const;
    const std::vector<GeometryBufferAttribute> &GetAttributes() const;

    const Mesh &operator=(const Mesh &);
    Mesh &operator=(Mesh &&);
};

class SceneObject;

class GeometryBuffer
{
  private:
    GLuint vao;
    GLuint vbo;
    GLuint ibo;

  public:
    GeometryBuffer();
    GeometryBuffer(const Mesh &);
    ~GeometryBuffer();

    bool Buffer(const Mesh &, SceneObject &out);

    void Bind();
};

struct SceneObjectUboData
{
    glm::mat4 modelMatrix;
    glm::mat3 normalMatrix;
};

class SceneObject : public StaticUboOwner<SceneObjectUboData>
{
  private:
    int bufferOffset;
    int indexCount;
    int offset;
    int drawMode;
    int indexType;

    GeometryBuffer *geometry;
    bool geometryManaged;

  public:
    SceneObject(GeometryBuffer *data, int bufferOffset, int indexCount, int offset, int drawMode, int indexType, bool manageGeometryBuffer = false);
    SceneObject(GeometryBuffer *, const Mesh &);
    SceneObject(const SceneObject &copy);
    SceneObject(SceneObject &&copy);
    SceneObject(const Mesh &);
    ~SceneObject();

    const glm::mat4 &GetModelMatrix() const;
    void SetModelMatrix(const glm::mat4 &);

    void Render();
};

struct CameraUboData
{
    glm::mat4 viewMat;
    glm::mat4 inverseViewMat;
    glm::mat4 projectionMat;
    glm::mat4 inverseProjectionMat;
};

class Camera : public StaticUboOwner<CameraUboData>
{
  private:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 direction;
    float fov;
    float near;
    float far;
    float aspectRation;

    bool viewDirty;
    bool projectionDirty;

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

    const glm::mat4 &GetViewMatrix() const;
    const glm::mat4 &GetProjectionMatrix() const;
    const glm::vec3 &GetPosition() const;
    const glm::vec3 &GetUp() const;
    const glm::vec3 &GetViewDirection() const;
    float GetFov() const;
    float GetNear() const;
    float GetFar() const;
    float GetAspectRation() const;
};

enum class TextureFormat
{
    FromFileExtension,
    JPEG,
    PNG,
    BMP,
    Binary,
};

class Texture
{
  private:
    int format;
    int internalFormat;
    int target;
    int width;
    int height;
    GLuint tex;

    void DestroyGlObjects();

  public:
    Texture();
    ~Texture();

    bool LoadDataFromMemory(void *);
    bool LoadDataFromFunction(int (*func)(float x, float y));
    bool LoadData(const std::string &path, TextureFormat format = TextureFormat::FromFileExtension);

    void SetFormat(int);
    void SetInternalFormat(int);
    void SetTarget(int);
    void SetWidth(int);
    void SetHeight(int);

    void Bind(uint textureUnit);
};

struct SceneUboData
{
};

class Scene : public StaticUboOwner<SceneUboData>
{
  private:
    std::map<int, Mesh *> meshes;
    std::map<int, GeometryBuffer *> geometry;
    std::map<int, SceneObject *> objects;
    Camera camera;

  public:
    bool AddGeometry();

    void Render();
};
} // namespace glutil
