#pragma once

#include <string>
#include <vector>
#include "glm/glm.hpp"

namespace gui
{
class RawSceneObject
{
  private:
    std::string tag;
    id_t id;

    size_t vertexCount;
    size_t indexCount;
    size_t vertexDataSize;
    size_t indexDataSize;
    void *vertices;
    void *indices;
};

class AbstracSceneObject
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

class SceneBufferObject
{
  private:
    int vao;
    int vbo;
    int ibo;
};

class BufferAsset
{
    int count;
    int type;
    int stride;
    int offset;
    bool normalized;
};

class Scene
{
  private:
};
} // namespace gui
