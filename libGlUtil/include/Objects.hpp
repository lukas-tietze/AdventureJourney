#pragma once

#include <string>
#include <vector>
#include <map>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "Defs.hpp"
#include "data/Json.hpp"

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
    uint ubo;
    uint bindingTarget;
    bool dirty;
    size_t bufferSize;

protected:
    std::vector<TData> data;

public:
    DynamicUboOwner();

    void CreateGlObjects();
    void DestroyGlObjects();
    void Bind() const;
    void SetBindingTarget(int);
    void Upload(bool force = false);
    void Resize();
    void SetDirty();
};

#include "libGlUtil/src/Objects/DynamicUboOwner.inl"

class RenderToTextureBase
{
};

struct PostProcessingPipeLineUboData
{
    int width;
    int height;
};

class PostProcessingPipeLine : public RenderToTextureBase, public StaticUboOwner<PostProcessingPipeLineUboData>
{
private:
    bool dirty;
    bool useUboData;
    bool ready;
    bool autoUpdate;
    bool requireColors;
    bool requireDepthStencil;
    GLenum colorTextureTarget;
    GLenum depthStencilTextureTarget;

    GLuint quadVao;
    GLuint quadVbo;
    GLuint colorTexture;
    GLuint depthStencilTexture;
    GLuint fbo;
    GLuint rbo;

    int w;
    int h;

    void DestroyGlObjects();
    void Recreate();
    void TransferFrom(PostProcessingPipeLine &);

public:
    PostProcessingPipeLine();
    PostProcessingPipeLine(PostProcessingPipeLine &&);
    PostProcessingPipeLine(const PostProcessingPipeLine &) = delete;
    ~PostProcessingPipeLine();

    void SetColorsEnabled(bool);
    void SetDepthAndStencilEnabled(bool);
    void SetColorBufferTextureTarget(GLenum);
    void SetDepthStencilBufferTextureTarget(GLenum);
    void SetSize(int, int);
    void Update();
    void SetAutoUpdateEnabled(bool);
    void SetUseUboData(bool);

    bool IsReady() const;

    void StartRecording();
    void Render();

    PostProcessingPipeLine &operator=(PostProcessingPipeLine &&);
    PostProcessingPipeLine &operator=(const PostProcessingPipeLine &) = delete;
};

class MeshAttribute
{
private:
    int index;
    int type;
    int count;
    int offset;
    bool normalized;

public:
    MeshAttribute();
    MeshAttribute(int index, int count, int type, bool normalized, int offset);

    int GetIndex() const;
    int GetType() const;
    int GetCount() const;
    int GetOffset() const;
    bool IsNormalized() const;
};

class MeshBuffer
{
private:
    int vertexCount;
    int vertexSize;
    void *vertices;
    int indexCount;
    int indexSize;
    int indexType;
    void *indices;
    std::vector<MeshAttribute> attributes;
    int drawMode;
    bool dataManaged;

    int CalculateIndexSize(int);
    void CopyFrom(const MeshBuffer &);
    void TransferFrom(MeshBuffer &);

public:
    MeshBuffer();
    MeshBuffer(const MeshBuffer &);
    MeshBuffer(MeshBuffer &&);
    ~MeshBuffer();

    bool LoadFromJson(const std::string &path);
    bool LoadFromCg2vd(const std::string &path);
    bool LoadFromData(int vertexCount, int vertexSize, void *vertices,
                      int indexCount, int indexType, void *indices,
                      std::vector<MeshAttribute> attributes,
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
    const std::vector<MeshAttribute> &GetAttributes() const;

    const MeshBuffer &operator=(const MeshBuffer &);
    MeshBuffer &operator=(MeshBuffer &&);
};

class Mesh
{
private:
    GLuint vao;
    GLuint vbo;
    GLuint ibo;

    int indexCount;
    int drawMode;
    int indexType;

    void TransferFrom(Mesh &);
    void DestroyGlObjects();

    Mesh(const Mesh &) = delete;
    Mesh &operator=(const Mesh &) = delete;

public:
    Mesh();
    Mesh(const MeshBuffer &);
    Mesh(Mesh &&);
    ~Mesh();

    void LoadFromBuffer(const MeshBuffer &);
    bool LoadFromJson(const std::string &path);
    bool LoadFromCg2vd(const std::string &path);
    bool LoadFromData(int vertexCount, int vertexSize, void *vertices,
                      int indexCount, int indexType, void *indices,
                      std::vector<MeshAttribute> attributes,
                      int drawMode, bool managaData = false);

    void Draw();

    Mesh &operator=(Mesh &&);
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
    Mesh *geometry;

public:
    SceneObject();
    SceneObject(Mesh *);
    SceneObject(const SceneObject &copy);
    SceneObject(SceneObject &&copy);
    ~SceneObject();

    const glm::mat4 &GetModelMatrix() const;
    void SetModelMatrix(const glm::mat4 &);

    Mesh *GetGeometry();
    void SetGeometry(Mesh *);

    void Render();
    void Update(double delta);
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
struct LightSourceUboData
{
    glm::vec4 position_type;
    glm::vec4 color_ambientFactor;
    glm::vec4 spotDir_cutOff;
    glm::vec4 spotExponent_size_enabled; // z  unused!
    glm::mat4 worldSpaceToShadowMap;
};
#pragma pack(pop)

enum class LightType
{
    Directional,
    Point,
};

class LightSet : public DynamicUboOwner<LightSourceUboData>
{
    friend class ConstLight;
    friend class Light;

public:
    class ConstLight
    {
        friend LightSet;

    protected:
        size_t id;
        const LightSet *collection;

        ConstLight(const LightSet *, size_t);

    public:
        glm::vec3 GetPosition() const;
        LightType GetType() const;
        glm::vec3 GetColor() const;
        float GetAmbientFactor() const;
        bool IsActive() const;
    };

    class Light : public ConstLight
    {
        friend LightSet;

    private:
        LightSet *modifiableCollection;

        Light(LightSet *, size_t);

    public:
        Light &SetPosition(const glm::vec3 &);
        Light &SetType(LightType);
        Light &SetColor(const glm::vec3 &);
        Light &SetAmbientFactor(float);
        Light &SetActive(bool);
    };

    Light Add();
    void Clear();
    size_t Size() const;

    Light operator[](size_t i);
    ConstLight operator[](size_t i) const;
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
    bool Check();

public:
    Shader();
    Shader(const Shader &);
    Shader(Shader &&);
    ~Shader();

    GLuint GetId() const;

    bool LoadFrom(const std::string &path);
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
    bool Check();

public:
    Program();
    Program(const Program &);
    Program(Program &&);
    ~Program();

    void AttachAll(const std::initializer_list<Shader *> &);
    void Attach(Shader *);
    void Detach(Shader *);
    void Clear();
    bool Link();
    bool LinkAll(const std::initializer_list<Shader *> &);
    bool ReloadAll();
    void Use();

    Program &operator=(const Program &);
    Program &operator=(Program &&);
};

class Texture
{
private:
    template <uint PChannels>
    struct FormatConverter
    {
        uint8_t *operator()(uint8_t *target, uint32_t value) const;
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
    GLenum GetFormatFromChannelCount(int);
    int GetChannelCountFromFormat();

    template <class TBuilder, uint PChannels>
    bool LoadDataFromBuilderCore(const TBuilder &);
    template <class TBuilder, uint PChannels>
    bool LoadCubeMapFromBuilderCore(const TBuilder &);

public:
    Texture();
    ~Texture();

    bool CreateBuffer();
    bool CreateAsStencilBuffer();
    bool CreateAsDepthBuffer();
    bool CreateAsStencilAndDepthBuffer();
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
    GLuint GetId() const;

    void SetFormat(int);
    void SetInternalFormat(int);
    void SetDataType(int);
    void SetTarget(int);
    void SetSize(int w, int h);
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

enum class BitMapFontContent
{
    AZaz09Space,
    Ascii32To126,
    Custom,
};

struct BitMapFontInfo : public json::IJsonSerializable
{
    int offsetX;
    int offsetY;
    int strideX;
    int strideY;
    int charWidth;
    int charHeight;
    int width;
    int height;
    BitMapFontContent content;
    std::string charList;

    void Load(const std::string &path);
    json::Node *Serialize();
    void Deserialize(const json::Node *);
};

#pragma pack(push, 1)
struct BitMapFontUboData
{
    glm::vec2 offset;
    glm::vec2 charSize;
    glm::vec2 stride;
    glm::vec2 linesAndCols;
};
#pragma pack(pop)

class BitMapFont : public StaticUboOwner<BitMapFontUboData>
{
private:
    int offsetX;
    int offsetY;
    int imgWidth;
    int imgHeight;
    int strideX;
    int strideY;
    int charWidth;
    int charHeight;
    int width;
    int height;

    GLuint tex;

    void DestroyGlObjects();
    void TransferFrom(BitMapFont &);

public:
    BitMapFont();
    BitMapFont(int offsetX, int offsetY, int strideX, int strideY, int charWidth, int charHeight);
    BitMapFont(const BitMapFont &) = delete;
    BitMapFont(BitMapFont &&);
    ~BitMapFont();

    void SetOffsetPx(int x, int y);
    void SetStridePx(int x, int y);
    void SetCharSizePx(int w, int h);
    void SetClipSize(int w, int h);
    bool LoadTexture(const std::string &);
    bool Load(const std::string &);
    bool Load(const BitMapFontInfo &);

    void Bind(GLenum target);
    glm::vec4 GetTexCoords(char c);

    BitMapFont &operator=(BitMapFont &&);
    BitMapFont &operator=(const BitMapFont &) = delete;
};

class TextImageFactory
{
private:
    void DestroyGlObjects();
    void TransferFrom(TextImageFactory &);

public:
    TextImageFactory();
    TextImageFactory(const TextImageFactory &) = delete;
    TextImageFactory(TextImageFactory &&);

    int DrawStringToTxture(const std::string &, const BitMapFont &, const Texture *);

    TextImageFactory &operator=(const TextImageFactory &) = delete;
    TextImageFactory &operator=(TextImageFactory &&);
};

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
    typedef std::string resourceId_t;

    template <class TKey, class TValue>
    bool DeleteItem(std::map<TKey, TValue *> &map, const TKey &key);
    template <class TKey, class TValue>
    TValue *FindOrCreateItem(std::map<TKey, TValue *> &map, const TKey &key);
    template <class TKey, class TValue>
    const TValue *FindItemOrNull(const std::map<TKey, TValue *> &map, const TKey &key) const;
    template <class TKey, class TValue>
    void DeleteAll(std::map<TKey, TValue *> &map);

    std::map<resourceId_t, SceneObject *> objects;
    std::map<resourceId_t, Material *> materials;
    std::map<resourceId_t, Program *> programs;
    std::map<resourceId_t, Texture *> textures;
    std::map<resourceId_t, Shader *> shaders;
    std::map<resourceId_t, Camera *> cameras;
    std::map<resourceId_t, Mesh *> meshs;
    std::map<resourceId_t, LightSet *> lightSets;

    Camera *activeCamera;
    LightSet *activeLightSet;

public:
    Scene();
    ~Scene();

    SceneObject *GetObject(const resourceId_t &);
    Material *GetMaterial(const resourceId_t &);
    Program *GetProgram(const resourceId_t &);
    Texture *GetTexture(const resourceId_t &);
    Shader *GetShader(const resourceId_t &);
    Camera *GetCamera(const resourceId_t &);
    Mesh *GetMesh(const resourceId_t &);
    LightSet *GetLightSet(const resourceId_t &);

    const SceneObject *GetObject(const resourceId_t &) const;
    const Material *GetMaterial(const resourceId_t &) const;
    const Program *GetProgram(const resourceId_t &) const;
    const Texture *GetTexture(const resourceId_t &) const;
    const Shader *GetShader(const resourceId_t &) const;
    const Camera *GetCamera(const resourceId_t &) const;
    const Mesh *GetMesh(const resourceId_t &) const;
    const LightSet *GetLightSet(const resourceId_t &) const;

    bool RemoveObject(const resourceId_t &);
    bool RemoveMaterial(const resourceId_t &);
    bool RemoveProgram(const resourceId_t &);
    bool RemoveTexture(const resourceId_t &);
    bool RemoveShader(const resourceId_t &);
    bool RemoveCamera(const resourceId_t &);
    bool RemoveMesh(const resourceId_t &);
    bool RemoveLightSet(const resourceId_t &);

    Shader *InitShader(const resourceId_t &, const std::string &sourcePath);
    Program *InitProgram(const resourceId_t &, const std::initializer_list<std::string> &shaderNames);
    Program *InitProgramFromSources(const resourceId_t &, const std::initializer_list<std::string> &sources);

    void ReloadAllShaders();

    void SetActiveCamera(const resourceId_t &);
    void SetActiveLightSet(const resourceId_t &);

    void Render();
    void Update(double delta);
};

#include "libGlUtil/src/Objects/Scene.inl"
} // namespace glutil