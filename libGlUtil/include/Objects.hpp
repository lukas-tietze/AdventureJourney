#pragma once

#include <string>
#include <vector>
#include <map>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "Defs.hpp"

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

#include "libGlUtil/src/Objects/StaticUboOwner.inl"

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

#include "libGlUtil/src/Objects/DynamicUboOwner.inl"

class FboStage
{
private:
    bool requireColorValues;
    bool requireDepthValues;
    bool requireStencilValue;
};

class FboPipeLine
{
private:
    std::vector<FboStage> stages;
};

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

#pragma pack(push, 1)
struct SceneObjectUboData
{
    glm::mat4 modelMatrix;
    glm::mat3 normalMatrix;
};
#pragma pack(pop)

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

#pragma pack(push, 1)
struct CameraUboData
{
    glm::mat4 viewMat;
    glm::mat4 inverseViewMat;
    glm::mat4 projectionMat;
    glm::mat4 inverseProjectionMat;
};
#pragma pack(pop)

class Camera : public StaticUboOwner<CameraUboData>
{
private:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 direction;
    float fov;
    float nearPlane;
    float farPlane;
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
    void SetNear(float nearPlane);
    void SetFar(float farPlane);
    void SetRange(float nearPlane, float farPlane);
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

#pragma pack(push, 1)
struct LigthSourceUboData
{
    ////falls w = 1 -> xyz = Richtung
    ////falls w = 0 -> xyz = Position
    glm::vec4 position;
    ////rgb = Color
    ////a = ambient factor
    glm::vec4 color;
    bool active;
};
#pragma pack(pop)

class LigthSource : StaticUboOwner<LigthSourceUboData>
{
public:
    LigthSource();
    LigthSource(const glm::vec3 &position, bool directionalLigth, const glm::vec3 &color, float ambientFactor, bool active);

    const glm::vec3 &GetPosition() const;
    bool IsDirectionalLigth() const;
    const glm::vec3 &GetColor() const;
    float GetAmbientFactor() const;
    bool IsActive() const;

    void SetPosition(const glm::vec3 &);
    void SsDirectionalLigth(bool);
    void SetColor(const glm::vec3 &);
    void SetAmbientFactor(float);
    void SetActive(bool);
};

class LigthSourceCollection : DynamicUboOwner<LigthSourceUboData>
{
public:
    LigthSourceCollection();
    LigthSourceCollection(const std::initializer_list<LigthSource> &);

    void Add(const LigthSource &);
    void Clear();
};

#pragma pack(push, 1)
struct MaterialUboData
{
    glm::vec4 ambientColor;
    glm::vec4 diffuseColor;
    glm::vec4 specularColor;
    float shininess;
};
#pragma pack(pop)

class Material : StaticUboOwner<MaterialUboData>
{
public:
    Material();
    Material(const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, float shininess);
};

class MaterialCollection : DynamicUboOwner<MaterialUboData>
{
    MaterialCollection();
    MaterialCollection(const std::initializer_list<Material> &);

    void Add(const Material &);
    void Clear();
};

enum class ImageFormat
{
    FromFileExtension,
    JPEG,
    PNG,
    BMP,
    Binary,
};

class Shader
{
    friend std::ostream &operator<<(std::ostream &, const Shader &);

private:
    std::string path;
    GLenum type;
    GLuint id;

    void DestroyGlObjects();
    void CopyFrom(const Shader &);
    void TransferFrom(Shader &);

public:
    Shader();
    Shader(const Shader &);
    Shader(Shader &&);
    ~Shader();

    GLuint GetId() const;

    bool LoadFrom(const std::string &path, GLenum type);
    bool Reload();

    Shader &operator=(const Shader &);
    Shader &operator=(Shader &&);
};

std::ostream &operator<<(std::ostream &, const Shader &);

class Program
{
private:
    std::vector<Shader *> shaders;
    GLuint id;

    void DestroyGlObjects();
    void CopyFrom(const Program &);
    void TransferFrom(Program &);

public:
    Program();
    Program(const Program &);
    Program(Program &&);
    ~Program();

    void AttachShader(Shader *);
    void DetachShader(Shader *);
    void Clear();
    bool Link();
    bool ReloadAll();
    void Use();

    Program &operator=(const Program &);
    Program &operator=(Program &&);
};

class Texture
{
private:
    template <uint PChannels>
    class FormatConverter
    {
        void *operator()(uint8_t *target, uint32_t value) const;
    };

    int format;
    int internalFormat;
    int target;
    GLenum dataType;
    GLsizei width;
    GLsizei height;
    GLenum wrapModes[3];
    GLenum filterModes[2];
    bool createMipmaps;
    double maxAnisotropy;
    GLuint tex;

    void DestroyGlObjects();
    void PrepareLoad();
    void SetTextureParameters();
    int GetChannelCountFromFormat();

    template <class TBuilder, uint PChannels>
    bool LoadDataFromBuilderCore(const TBuilder &);
    template <class TBuilder, uint PChannels>
    bool LoadCubeMapFromBuilderCore(const TBuilder &);

public:
    Texture();
    ~Texture();

    bool LoadDataFromMemory(void *);
    template <class TBuilder>
    bool LoadDataFromBuilder(const TBuilder &);
    bool LoadData(const std::string &path, ImageFormat format = ImageFormat::FromFileExtension);
    bool LoadCubeMap(const std::string &directory, const std::initializer_list<std::string> &files);
    bool LoadCubeMap(const std::initializer_list<std::string> &files);
    bool LoadCubeMap(const std::vector<std::string> &paths);
    bool LoadCubeMap(const std::string &directory, const std::vector<std::string> &files);
    bool LoadCubeMapFromMemory(const void **);
    template <class TBuilder>
    bool LoadCubeMapFromBuilder(const TBuilder &);

    void Bind(GLuint textureUnit);

    void SetFormat(int);
    void SetInternalFormat(int);
    void SetDataType(int);
    void SetTarget(int);
    void SetWidth(int);
    void SetHeight(int);
    void SetMipmapsEnabled(bool);
    void SetFilterMode(GLenum);
    void SetMinFilterMode(GLenum);
    void SetMagFilterMode(GLenum);
    void SetWrapMode(GLenum);
    void SetWrapModeR(GLenum);
    void SetWrapModeS(GLenum);
    void SetWrapModeT(GLenum);
    void SetMaxAnisotropy(double);
    void SetAnisotropicFilterDisabled();
};

#include "libGlUtil/src/Objects/Texture.inl"
#include "libGlUtil/src/Objects/FormatConverter.inl"

class TextOverlay
{
};

#pragma pack(push, 1)
struct SceneOverlayUboData
{
};
#pragma pack(pop)

class SceneOverlay : public StaticUboOwner<SceneOverlayUboData>
{
};

#pragma pack(push, 1)
struct SceneUboData
{
};
#pragma pack(pop)

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