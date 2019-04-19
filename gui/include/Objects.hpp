#pragma once

#include <string>
#include <vector>
#include "glm/glm.hpp"

namespace gui
{
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

class Geometry
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
    Geometry();

    bool LoadFromJson(const std::string &path);
    bool LoadFromCg2vd(const std::string &path);
    bool LoadFromData(int vertexCount, int vertexDataSize, void *vertices, int indexCount, int indexDataSize, void *indices, std::vector<GeometryBufferAttribute> attributes);

    int GetVertexCount() const;
    int GetIndexCount() const;
    int GetVertexDataSize() const;
    int GetIndexDataSize() const;
    const std::vector<GeometryBufferAttribute> &GetAttributes() const;
};

template <class TData, int bindingTarget>
class UboOwnerBase
{
private:
    int ubo;
    bool dirty;

protected:
    TData data;

public:
    UboOwnerBase();

    void CreateGlObjects();
    void DestroyGlObjects();
    void Bind() const;
    void Upload() const;
    void SetDirty();
};

#include "gui/src/Inline/Objects/UboOwnerBase.inl"

class AbstractSceneObject
{
private:
};

class SceneObjectData
{
private:
    int indexCount;
    int offset;
    int drawType;
};

class Scene
{
private:
public:
    bool AddGeometry();
};
} // namespace gui
