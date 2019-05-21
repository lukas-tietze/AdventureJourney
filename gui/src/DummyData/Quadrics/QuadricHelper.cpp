#include "QuadricHelper.internal.hpp"
#include <limits>
#include <iomanip>
#include "data/Math.hpp"
#include "data/Io.hpp"
#include "data/IteratorUtils.hpp"

gui::quadrics::QuadricContext::QuadricContext(const QuadricConfig &config) : config(config),
                                                                             vertices(),
                                                                             indices(),
                                                                             current()
{
}

gui::quadrics::pos_t &gui::quadrics::QuadricContext::Pos()
{
    return this->current.pos;
}

gui::quadrics::normal_t &gui::quadrics::QuadricContext::Normal()
{
    return this->current.normal;
}

gui::quadrics::color_t &gui::quadrics::QuadricContext::Color()
{
    return this->current.color;
}

gui::quadrics::texCoord_t &gui::quadrics::QuadricContext::TexCoord()
{
    return this->current.texCoord;
}

size_t gui::quadrics::QuadricContext::VertexCount() const
{
    return this->vertices.size();
}

size_t gui::quadrics::QuadricContext::IndexCount() const
{
    return this->indices.size();
}

gui::quadrics::QuadricVertex &gui::quadrics::QuadricContext::Current()
{
    return this->current;
}

std::vector<gui::quadrics::vertex_t> &gui::quadrics::QuadricContext::Vertices()
{
    return this->vertices;
}

std::vector<gui::quadrics::index_t> &gui::quadrics::QuadricContext::Indices()
{
    return this->indices;
}

void gui::quadrics::QuadricContext::Reserve(size_t v, size_t i)
{
    this->vertices.reserve(v);
    this->indices.reserve(i);
}

void gui::quadrics::QuadricContext::SetTexCoords(float s, float t)
{
    auto transformedCoords = glm::vec2(s, t) * this->config.texCoordScale + this->config.texCoordOffset;

    this->current.texCoord.s = static_cast<uint16_t>(util::Crop(transformedCoords.s, 0.f, 1.f) * static_cast<float>(std::numeric_limits<uint16_t>::max()));
    this->current.texCoord.t = static_cast<uint16_t>(util::Crop(transformedCoords.t, 0.f, 1.f) * static_cast<float>(std::numeric_limits<uint16_t>::max()));
}

void gui::quadrics::QuadricContext::SetPositionAndNormal(float x, float y, float z)
{
    this->SetPosition(x, y, z);
    this->SetNormal(x, y, z);
}

void gui::quadrics::QuadricContext::SetPosition(float x, float y, float z)
{
    this->current.pos.x = x;
    this->current.pos.y = y;
    this->current.pos.z = z;
}

void gui::quadrics::QuadricContext::SetNormal(float x, float y, float z)
{
    this->current.normal.x = x;
    this->current.normal.y = y;
    this->current.normal.z = z;
}

void gui::quadrics::QuadricContext::SetPositionAndNormal(const glm::vec3 &v)
{
    SetPosition(v);
    SetNormal(v);
}

void gui::quadrics::QuadricContext::SetSphericalTexCoords()
{
    this->SetTexCoords(std::asin(this->current.pos.z) / (2 * M_PI) + 0.5,
                       std::atan(this->current.pos.y / this->current.pos.x) / (2.0 * M_PI) + 0.5);
}

void gui::quadrics::QuadricContext::SetPosition(const glm::vec3 &v)
{
    this->current.pos = v;
}

void gui::quadrics::QuadricContext::SetNormal(const glm::vec3 &v)
{
    this->current.normal = v;
}

void gui::quadrics::QuadricContext::Push()
{
    this->current.color = this->config.useColorFunc
                              ? this->config.colorFunc(this->current.pos)
                              : this->config.color;

    this->vertices.push_back(this->current);
}

void gui::quadrics::QuadricContext::PushTriangle(index_t i1, index_t i2, index_t i3)
{
    this->indices.push_back(i1);
    this->indices.push_back(i2);
    this->indices.push_back(i3);
}

void gui::quadrics::QuadricContext::PushTriangle(const index_t *i)
{
    this->indices.push_back(i[0]);
    this->indices.push_back(i[1]);
    this->indices.push_back(i[2]);
}

void gui::quadrics::QuadricContext::PushQuad(index_t i1, index_t i2, index_t i3, index_t i4)
{
    this->indices.push_back(i1);
    this->indices.push_back(i3);
    this->indices.push_back(i2);

    this->indices.push_back(i1);
    this->indices.push_back(i4);
    this->indices.push_back(i3);
}

void gui::quadrics::QuadricContext::PushQuad(const index_t *i)
{
    this->indices.push_back(i[0]);
    this->indices.push_back(i[2]);
    this->indices.push_back(i[1]);

    this->indices.push_back(i[0]);
    this->indices.push_back(i[3]);
    this->indices.push_back(i[2]);
}

void gui::quadrics::QuadricContext::PushIndices(const std::initializer_list<index_t> &list)
{
    for (auto index : list)
        this->indices.push_back(index);
}

bool gui::quadrics::QuadricContext::CreateMesh(glutil::Mesh &out)
{
    util::dbg.WriteLine("Created Quadric with % vertices and % indices.\nVertices: {%}\nIndices: %",
                        this->vertices.size(),
                        this->indices.size(),
                        util::WrapIterable(this->vertices.begin(), this->vertices.end(), "}, {"),
                        util::WrapIterable(this->indices.begin(), this->indices.end(), ", "));

    out.LoadFromData(this->vertices.size(), sizeof(QuadricVertex), this->vertices.data(),
                     this->indices.size(), GL_UNSIGNED_SHORT, this->indices.data(),
                     {
                         glutil::MeshAttribute(0, 3, GL_FLOAT, false, offsetof(QuadricVertex, QuadricVertex::pos)),
                         glutil::MeshAttribute(1, 3, GL_FLOAT, false, offsetof(QuadricVertex, QuadricVertex::normal)),
                         glutil::MeshAttribute(2, 4, GL_UNSIGNED_BYTE, true, offsetof(QuadricVertex, QuadricVertex::color)),
                         glutil::MeshAttribute(3, 2, GL_UNSIGNED_SHORT, true, offsetof(QuadricVertex, QuadricVertex::texCoord)),
                     },
                     GL_TRIANGLES, true);

    return true;
}

std::ostream &gui::quadrics::operator<<(std::ostream &s, const QuadricVertex &v)
{
    auto flags = s.flags();

    s << "pos={" << v.pos.x << ", " << v.pos.y << ", " << v.pos.z
      << "}, normal={" << v.normal.x << ", " << v.normal.y << ", " << v.normal.z
      << "}, texCoord={" << v.texCoord.s << ", " << v.texCoord.t
      << "}, color=#" << std::hex << v.color;

    s.flags(flags);

    return s;
}