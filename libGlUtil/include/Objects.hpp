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
class UboOwner
{
private:
    GLuint ubo;
    GLuint bindingTarget;
    bool contentDirty;
    bool bufferDirty;
    void *data;
    size_t dataSize;
    bool autoUpdate;

public:
    UboOwner();
    ~UboOwner();

    void CreateGlObjects();
    void DestroyGlObjects();
    void Bind() const;
    void SetBindingTarget(int);
    void Upload(bool force = false);
    void SetDirty();
    void SetData(void *data, size_t size);
    void Update(bool force = false);
    void SetAutoUpdate(bool);
};

template <class TData>
class StaticUboOwner : public UboOwner
{
protected:
    TData data;

public:
    StaticUboOwner();
};

#include "libGlUtil/src/Objects/StaticUboOwner.inl"

template <class TData>
class VectoredUboOwner : public UboOwner
{
protected:
    std::vector<TData> data;

    void Resize();

public:
    VectoredUboOwner();

    TData &Add();
    TData &Add(const TData &);
    void Clear();
    size_t Size() const;
    bool Remove(const TData &);
    bool RemoveAt(int index);

    TData &operator[](size_t i);
    const TData &operator[](size_t i) const;
};

#include "libGlUtil/src/Objects/VectoredUboOwner.inl"

template <class TData, class TAccessor, class TConstAccessor>
class UboSet : public VectoredUboOwner<TData>
{
public:
    TAccessor Add();
    void Clear();

    TAccessor operator[](size_t index);
    TConstAccessor operator[](size_t index) const;
};

#include "libGlUtil/src/Objects/UboSet.inl"

struct RenderToTextureUboData
{
    int width;
    int height;
};

class RenderToTextureBase : public StaticUboOwner<RenderToTextureUboData>
{
private:
    bool dirty;
    bool useUboData;
    bool ready;
    bool autoUpdate;

    GLuint fbo;

    bool CheckBeforUsage();
    void DestroyFrameBuffer();
    void CreateFrameBuffer();
    void ValidateFrameBuffer();

protected:
    virtual void Recreate();

    virtual void FillFrameBuffer() = 0;

    virtual void BeginRender();
    virtual void EndRender();
    void TransferFrom(RenderToTextureBase &);
    void BindFbo();
    void SetFrameBufferDirty();

public:
    RenderToTextureBase();
    RenderToTextureBase(RenderToTextureBase &&);
    RenderToTextureBase(const RenderToTextureBase &) = delete;
    virtual ~RenderToTextureBase();

    void SetSize(int, int);
    void Update();
    void SetAutoUpdateEnabled(bool);
    void SetUseUboData(bool);

    int GetWidth() const;
    int GetHeight() const;

    bool IsDirty() const;
    bool IsReady() const;
    void StartRecording();
    void Render();

    RenderToTextureBase &operator=(RenderToTextureBase &&);
    RenderToTextureBase &operator=(const RenderToTextureBase &) = delete;
};

class DeferredRenderingPipeline : public RenderToTextureBase
{
private:
    GLuint textures[4];
    GLuint targets[4];

protected:
    virtual void DestroyGlObjects();
    virtual void TransferFrom(DeferredRenderingPipeline &);

    virtual void FillFrameBuffer();
    virtual void BeginRender();
    virtual void EndRender();

public:
    DeferredRenderingPipeline();
    DeferredRenderingPipeline(DeferredRenderingPipeline &&);
    DeferredRenderingPipeline(const DeferredRenderingPipeline &) = delete;
    virtual ~DeferredRenderingPipeline();

    void SetNormalTexureBindingTarget(GLuint);
    void SetMaterialTexureBindingTarget(GLuint);
    void SetAlbedoTexureBindingTarget(GLuint);
    void SetDepthTexureBindingTarget(GLuint);

    DeferredRenderingPipeline &operator=(const DeferredRenderingPipeline &) = delete;
    DeferredRenderingPipeline &operator=(DeferredRenderingPipeline &&);
};

class Texture;
class Program;

class SkyBox
{
private:
    Texture *texture;
    Program *program;
    GLuint textureUnit;

public:
    SkyBox();

    void SetProgram(Program *);
    void SetTexture(Texture *, GLuint);
    void Render();
};

class PostProcessingPipeline : public RenderToTextureBase
{
private:
    bool requireColors;
    bool requireDepthStencil;
    GLenum colorTextureTarget;
    GLenum depthStencilTextureTarget;

    GLuint colorTexture;
    GLuint depthStencilTexture;
    GLuint rbo;

protected:
    virtual void DestroyGlObjects();
    virtual void TransferFrom(PostProcessingPipeline &);

    virtual void FillFrameBuffer();
    virtual void BeginRender();
    virtual void EndRender();

public:
    PostProcessingPipeline();
    PostProcessingPipeline(PostProcessingPipeline &&);
    PostProcessingPipeline(const PostProcessingPipeline &) = delete;
    virtual ~PostProcessingPipeline();

    void SetColorsEnabled(bool);
    void SetDepthAndStencilEnabled(bool);
    void SetColorBufferTextureTarget(GLenum);
    void SetDepthStencilBufferTextureTarget(GLenum);

    PostProcessingPipeline &operator=(PostProcessingPipeline &&);
    PostProcessingPipeline &operator=(const PostProcessingPipeline &) = delete;
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

public:
    Mesh();
    Mesh(const MeshBuffer &);
    Mesh(const Mesh &) = delete;
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
    Mesh &operator=(const Mesh &) = delete;
};

#pragma pack(push, 1)
struct SceneObjectUboData
{
    glm::mat4 modelMatrix;
    glm::mat4 normalMatrix;
    int materialId;
};
#pragma pack(pop)

class Program;
class Material;

class SceneObject : public StaticUboOwner<SceneObjectUboData>
{
private:
    Mesh *geometry;
    Material *material;

public:
    SceneObject();
    SceneObject(Mesh *);
    SceneObject(const SceneObject &copy);
    SceneObject(SceneObject &&copy);
    ~SceneObject();

    void SetGeometry(Mesh *);
    void SetMaterial(Material *);
    void SetModelMatrix(const glm::mat4 &);
    const glm::mat4 &GetModelMatrix() const;
    Mesh *GetGeometry();
    const Mesh *GetGeometry() const;
    Material *GetMaterial();
    const Material *GetMaterial() const;

    void Render();
    void RenderDepthPass();
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

class CameraUpdater
{
private:
    int keys[6];
    float moveSpeed[6];
    float rotateSpeed[2];
    bool flattenMove;
    bool enabled;
    bool invertVerticalRotation;
    Camera *camera;

public:
    CameraUpdater();

    void Update(double delta);

    void SetKeyForward(int);
    void SetKeyBack(int);
    void SetKeyLeft(int);
    void SetKeyRight(int);
    void SetKeyUp(int);
    void SetKeyDown(int);
    void SetKeys(int, int, int, int, int, int);
    void SetRotateSpeed(float, float);
    void SetVerticalRotateSpeed(float);
    void SetHorizontalSpeed(float);
    void SetMovementSpeed(float);
    void SetFlattenMove(bool);
    void Enable();
    void Disable();
    void SetEnabled(bool);
    void SetCamera(Camera *);

    Camera *GetCamera();
    const Camera *GetCamera() const;
};

enum class LightType
{
    Directional,
    Point,
};

#pragma pack(push, 1)
class Light
{
private:
    glm::vec4 position_type;
    glm::vec4 color_ambientFactor;
    glm::vec4 spotDir_cutOff;
    glm::vec4 spotExponent_size_enabled; // z  unused!
    glm::mat4 worldSpaceToShadowMap;

public:
    glm::vec3 GetPosition() const;
    Light &SetPosition(const glm::vec3 &);

    LightType GetType() const;
    Light &SetType(LightType);

    float GetAmbientFactor() const;
    Light &SetAmbientFactor(float);

    bool IsActive() const;
    Light &SetActive(bool);

    glm::vec3 GetColor() const;
    Light &SetColor(const glm::vec3 &);
};
#pragma pack(pop)

typedef VectoredUboOwner<Light> LightSet;

#pragma pack(push, 1)
struct MaterialUboData
{
    glm::vec4 albedo;
    glm::vec4 shininess_metalness;
};
#pragma pack(pop)

class Texture;

class Material : public StaticUboOwner<MaterialUboData>
{
private:
    Texture *normalMap;
    GLenum normalMapTarget;
    Texture *albedoMap;
    GLenum albedoMapTarget;
    Texture *propertyMap;
    GLenum propertyMapTarget;

public:
    Material();

    void SetAlbedo(const glm::vec4 &);
    void SetShininess(float);
    void SetMetalness(float);
    void SetNormalMap(Texture *map, GLenum target);
    void SetAlbedoMap(Texture *map, GLenum target);
    void SetPropertyMap(Texture *map, GLenum target);

    const glm::vec4 &GetAlbedo(const glm::vec4 &) const;
    float GetShininess(float) const;
    float GetMetalness(float) const;

    void Use();
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

    bool LoadCubeMapCore(const std::vector<std::string> &);
    bool LoadCubeMapCore(const void *const *);

public:
    Texture();
    ~Texture();

    bool LoadDataFromMemory(void *);
    template <class TBuilder>
    bool LoadDataFromBuilder(const TBuilder &);
    bool LoadData(const std::string &path);
    bool LoadCubeMap(const std::string &directory, const std::string &extension);
    bool LoadCubeMap(const std::vector<std::string> &paths);
    bool LoadCubeMap(const std::string &directory, const std::vector<std::string> &files);
    bool LoadCubeMapFromMemory(const void *const *);
    template <class TBuilder>
    bool LoadCubeMapFromBuilder(const TBuilder &);

    void Bind(GLuint textureUnit);
    GLuint GetId() const;
    GLuint DisownId();

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

enum class FontContent
{
    AZaz09Space,
    Ascii32To126,
    Custom,
};

std::ostream &operator<<(std::ostream &, FontContent);

enum class FontType
{
    BitMap,
    TrueType,
};

std::ostream &operator<<(std::ostream &, FontType);

struct FontInfo : public json::IJsonSerializable
{
    int offsetX;
    int offsetY;
    int strideX;
    int strideY;
    int charWidth;
    int charHeight;
    int rows;
    int cols;
    FontContent content;
    FontType type;
    std::string charList;
    std::string source;

    json::Node *Serialize();
    void Deserialize(const json::Node *);
};

#pragma pack(push, 1)
struct BitMapFontUboData
{
    ///Texturekoordinaten oben links
    glm::vec2 pos;
    ///Größe auf der Textur (pos + size = untere rechte Ecke)
    glm::vec2 size;
    ///Abstand von Baseline zum oberen linken Punkt
    glm::vec2 bearing;
    ///Abstand zum nächsten Character
    glm::vec2 advance;
};
#pragma pack(pop)

class BitMapFont : public VectoredUboOwner<BitMapFontUboData>
{
private:
    Texture tex;
    int charMapping[256];
    float lineHeight;

    void TransferFrom(BitMapFont &);
    bool LoadTexture(const FontInfo &);
    bool LoadCoordinates(const FontInfo &);
    bool LoadBitMapFont(const FontInfo &);
    bool LoadTrueTypeFont(const FontInfo &);

public:
    BitMapFont();
    BitMapFont(const BitMapFont &) = delete;
    BitMapFont(BitMapFont &&);
    ~BitMapFont();

    bool Load(const std::string &);
    bool Load(const FontInfo &);

    Texture *GetTexture();
    void Bind(GLenum target);
    bool HasChar(char c) const;
    bool CreateStringMesh(const std::string &text, Mesh *out);

    const BitMapFontUboData &operator[](char c) const;
    BitMapFont &operator=(BitMapFont &&);
    BitMapFont &operator=(const BitMapFont &) = delete;
};

class TextImageFactory
{
private:
    float lineSpacing;

    glm::vec2 CalcImageSize();

public:
    int DrawStringToTexture(const std::string &, const BitMapFont *, const Texture *);
    int DrawLinesToTexture(const std::vector<std::string> &, const BitMapFont *, const Texture *);

    TextImageFactory SetLineSpacing(float);
};

#pragma pack(push, 1)
struct SceneOverlayUboData
{
    glm::mat4 modelMatrix;
};
#pragma pack(pop)

class SceneOverlay : public StaticUboOwner<SceneOverlayUboData>
{
private:
    bool enabled;
    Mesh *mesh;
    Material *material;
    glm::vec2 scale;
    glm::vec2 pos;

    void TransferFrom(SceneOverlay &);
    void Update();

public:
    SceneOverlay();
    SceneOverlay(SceneOverlay &&);
    SceneOverlay(const SceneOverlay &) = delete;

    void SetEnabled(bool);
    bool IsEnabled() const;
    void SetText(const std::string &);
    void Render();

    SceneOverlay &operator=(SceneOverlay &&);
    SceneOverlay &operator=(const SceneOverlay &) = delete;
};

class RenderGroup
{
private:
public:
    RenderGroup();
    ~RenderGroup();
};

class Scene
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
    std::map<resourceId_t, BitMapFont *> fonts;
    std::map<resourceId_t, SceneOverlay *> overlays;

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
    BitMapFont *GetFont(const resourceId_t &);
    SceneOverlay *GetOverlay(const resourceId_t &);

    const SceneObject *GetObject(const resourceId_t &) const;
    const Material *GetMaterial(const resourceId_t &) const;
    const Program *GetProgram(const resourceId_t &) const;
    const Texture *GetTexture(const resourceId_t &) const;
    const Shader *GetShader(const resourceId_t &) const;
    const Camera *GetCamera(const resourceId_t &) const;
    const Mesh *GetMesh(const resourceId_t &) const;
    const LightSet *GetLightSet(const resourceId_t &) const;
    const BitMapFont *GetFont(const resourceId_t &) const;
    const SceneOverlay *GetOverlay(const resourceId_t &) const;

    bool RemoveObject(const resourceId_t &);
    bool RemoveMaterial(const resourceId_t &);
    bool RemoveProgram(const resourceId_t &);
    bool RemoveTexture(const resourceId_t &);
    bool RemoveShader(const resourceId_t &);
    bool RemoveCamera(const resourceId_t &);
    bool RemoveMesh(const resourceId_t &);
    bool RemoveLightSet(const resourceId_t &);
    bool RemoveFont(const resourceId_t &);
    bool RemoveOverlay(const resourceId_t &);

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