#pragma once

#include <vector>
#include <ostream>

#include "DummyData.hpp"

namespace gui
{
namespace quadrics
{
typedef glm::vec3 pos_t;
typedef glm::vec3 normal_t;
typedef uint32_t color_t;
typedef glm::vec<2, uint16_t> texCoord_t;

#pragma pack(push, 1)
struct QuadricVertex
{
    pos_t pos;
    normal_t normal;
    color_t color;
    texCoord_t texCoord;
};
#pragma pack(pop)

typedef QuadricVertex vertex_t;
typedef uint16_t index_t;

class QuadricContext
{
private:
    QuadricConfig config;

    std::vector<vertex_t> vertices;
    std::vector<index_t> indices;

    vertex_t current;
    std::string name;

public:
    QuadricContext(const QuadricConfig &, const std::string &);

    pos_t &Pos();
    normal_t &Normal();
    color_t &Color();
    texCoord_t &TexCoord();

    size_t VertexCount() const;
    size_t IndexCount() const;

    QuadricVertex &Current();

    std::vector<vertex_t> &Vertices();
    std::vector<index_t> &Indices();

    void Reserve(size_t, size_t);
    void SetTexCoords(float s, float t);
    void SetSphericalTexCoords();
    void SetPositionAndNormal(float x, float y, float z);
    void SetPositionAndNormal(const glm::vec3 &);
    void SetPosition(float x, float y, float z);
    void SetPosition(const glm::vec3 &);
    void SetNormal(float x, float y, float z);
    void SetNormal(const glm::vec3 &);
    void Push();
    void PushTriangle(index_t, index_t, index_t);
    void PushTriangle(const index_t *);
    void PushQuad(index_t, index_t, index_t, index_t);
    void PushQuad(const index_t *);
    void PushIndices(const std::initializer_list<index_t> &);

    bool CreateMesh(glutil::Mesh &out);
};

std::ostream &operator<<(std::ostream &, const QuadricVertex &);
} // namespace quadrics
} // namespace gui