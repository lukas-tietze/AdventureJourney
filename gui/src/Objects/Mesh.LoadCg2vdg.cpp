#include "Objects.hpp"

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <vector>
namespace
{
enum CG2VDTypeID : uint32_t
{
    CG2_BYTE = 0x1400,               // == GL_BYTE
    CG2_UBYTE = 0x1401,              // == GL_UNSIGNED_BYTE
    CG2_SHORT = 0x1402,              // == GL_SHORT
    CG2_USHORT = 0x1403,             // == GL_UNSIGNED_SHORT
    CG2_INT = 0x1404,                // == GL_INT
    CG2_UINT = 0x1405,               // == GL_UNSIGNED_INT
    CG2_HALF_FLOAT = 0x140B,         // == GL_HALF_FLOAT
    CG2_FLOAT = 0x1406,              // == GL_FLOAT
    CG2_DOUBLE = 0x140A,             // == GL_DOUBLE
    CG2_INT_2_10_10_10_REV = 0x8D9F, // == GL_INT_2_10_10_10_REV
    CG2_UINT_2_10_10_10_REV = 0x8368 // == GL_UNSIGNED_INT_2_10_10_10_REV
};

enum CG2VDPrimitiveID : uint32_t
{
    CG2_POINTS = 0x0000,         // == GL_POINTS
    CG2_LINES = 0x0001,          // == GL_LINES
    CG2_LINE_LOOP = 0x0002,      // == GL_LINE_LOOP
    CG2_LINE_STRIP = 0x0003,     // == GL_LINE_STRIP
    CG2_TRIANGLES = 0x0004,      // == GL_TRIANGLES
    CG2_TRIANGLE_STRIP = 0x0005, // == GL_TRIANGLE_STRIP
    CG2_TRIANGLE_FAN = 0x0006    // == GL_TRIANGLE_FAN
};

enum CG2VDAttributeID : uint32_t
{
    CG2_POSITION = 0x0000,
    CG2_NORMAL,
    CG2_TANGENT,
    CG2_BITANGENT,
    CG2_TEXTURE_COODINATE,
    CG2_COLOR,
    CG2_BONE_WEIGTHS,
    CG2_BONE_IDS,
    CG2_BONE_COUNT,
    CG2_LAST = CG2_BONE_COUNT,
};

class CG2VDAttribute;

void Attribute_set(CG2VDAttribute &am, const uint32_t id, const CG2VDTypeID type, const uint32_t count, const uint32_t normalized, const uint32_t as_integer, const uint32_t offset);

struct CG2VDAttribute
{
    CG2VDAttribute()
    {
        Attribute_set(*this,
                      CG2VDAttributeID::CG2_POSITION,
                      CG2VDTypeID::CG2_FLOAT,
                      0, 0, 0, 0);

        internal_attrib_size = sizeof(internal_attrib_size) +
                               sizeof(attib_id) +
                               sizeof(type) +
                               sizeof(count) +
                               sizeof(normalized) +
                               sizeof(as_integer) +
                               sizeof(offset);
    }

    uint32_t internal_attrib_size; // Ignore this !!!
    uint32_t attib_id;             // id of this attribute.
    uint32_t type;                 // datatype of this attribute (one of CG2VDTypeID)
    uint32_t count;                // number of elements this attribute has (one of [1,4])
    uint32_t normalized;           // is the attribute normalized
    uint32_t as_integer;           // is this attribute ment to be an integer
    uint32_t offset;               // offset from the beginning of the vertex in bytes
};

struct CG2VDMeta
{
    CG2VDMeta()
    {
        primitive = CG2_TRIANGLES;
        index_type = CG2_UINT;
        num_vertices = 0;
        num_indices = 0;
        vertex_size = 0;

        internal_meta_size = sizeof(internal_meta_size) +
                             sizeof(primitive) +
                             sizeof(index_type) +
                             sizeof(num_vertices) +
                             sizeof(num_indices) +
                             sizeof(vertex_size) +
                             sizeof(num_attribs);
    }

    uint32_t internal_meta_size; // Ignore this !!!
    uint32_t primitive;          // the primitive type used to render this model
    uint32_t index_type;         // the index type (one of  UBYTE,USHORT or UINT)
    uint32_t num_vertices;       // number of vertices in the vertex array
    uint32_t num_indices;        // number of indeces in the index array
    uint32_t vertex_size;        // size of a single vertex (stride) in bytes
    uint32_t num_attribs;        // number of attributes (attributes.size())
    std::vector<CG2VDAttribute> attributes;
};

uint32_t Meta_get_index_data_size(const CG2VDMeta &m);
uint32_t Meta_get_vertex_data_size(const CG2VDMeta m);
void Meta_read(CG2VDMeta &m, FILE *f);
void Meta_read_data(const CG2VDMeta &m, void *index_data, void *vertex_data, FILE *f);

struct CG2VertexData
{
    // The meta information of the vertex data
    CG2VDMeta meta_data;
    // The index array
    void *index_data;
    // The interleaved vertex array
    void *vertex_data;

    CG2VertexData() { index_data = vertex_data = nullptr; }

    ~CG2VertexData()
    {
        free(index_data);
        index_data = nullptr;
        free(vertex_data);
        vertex_data = nullptr;
    }

    bool read(const std::string &path)
    {
        FILE *f = fopen(path.c_str(), "rb");
        if (!f)
            return false;
        meta_data.attributes.clear();

        Meta_read(meta_data, f);
        index_data = realloc(index_data,
                             Meta_get_index_data_size(meta_data));
        vertex_data = realloc(vertex_data,
                              Meta_get_vertex_data_size(meta_data));
        Meta_read_data(meta_data, index_data, vertex_data, f);
        fclose(f);
        return true;
    }

    uint32_t index_data_size() const
    {
        auto to_ret = Meta_get_index_data_size(meta_data);
        return to_ret;
    }

    uint32_t vertex_data_size() const
    {
        auto to_ret = Meta_get_vertex_data_size(meta_data);
        return to_ret;
    }
};

uint32_t Attribute_size(const CG2VDAttribute &am);
void Attribute_read(CG2VDAttribute &am, FILE *f);
void Meta_add_attribute(CG2VDMeta &m, const CG2VDAttribute &am);
void Meta_reeval_attributes(CG2VDMeta &m);

#define VD_READ_VAR(x, f) fread(&x, 1, sizeof(x), f)

void Attribute_set(CG2VDAttribute &am,
                   const uint32_t id,
                   const CG2VDTypeID type,
                   const uint32_t count,
                   const uint32_t normalized,
                   const uint32_t as_integer,
                   const uint32_t offset)
{
    am.attib_id = id;
    am.type = type;
    am.count = count;
    am.normalized = normalized;
    am.as_integer = as_integer;
    am.offset = offset;
}

void Attribute_read(CG2VDAttribute &am, FILE *f)
{
    size_t to_read, total_size;

    VD_READ_VAR(am.internal_attrib_size, f);
    total_size = to_read = am.internal_attrib_size - sizeof(am.internal_attrib_size);
    to_read -= VD_READ_VAR(am.attib_id, f);
    to_read -= VD_READ_VAR(am.type, f);
    to_read -= VD_READ_VAR(am.count, f);
    to_read -= VD_READ_VAR(am.normalized, f);
    to_read -= VD_READ_VAR(am.as_integer, f);
    to_read -= VD_READ_VAR(am.offset, f);

    assert(to_read <= total_size);
    fseek(f, static_cast<long>(to_read), SEEK_CUR);
}

//------------------------------------------------------------------------------

void Meta_add_attribute(CG2VDMeta &m, const CG2VDAttribute &am)
{
    m.attributes.push_back(am);
    m.num_attribs = static_cast<uint32_t>(m.attributes.size());
    m.vertex_size += static_cast<uint32_t>(Attribute_size(am));
}

void Meta_reeval_attributes(CG2VDMeta &m)
{
    uint32_t i = 0;
    m.vertex_size = 0;
    for (i = 0; i < m.attributes.size(); i++)
    {
        // The packed formats must represent four values so make sure that
        // there are 4 of them
        if (m.attributes[i].type == CG2_INT_2_10_10_10_REV ||
            m.attributes[i].type == CG2_UINT_2_10_10_10_REV)
            m.attributes[i].count = 4;
        m.attributes[i].offset = m.vertex_size;
        m.vertex_size += Attribute_size(m.attributes[i]);
    }
}

uint32_t Meta_get_index_data_size(const CG2VDMeta &m)
{
    if (m.index_type == CG2_UBYTE)
        return 1 * m.num_indices;
    else if (m.index_type == CG2_USHORT)
        return 2 * m.num_indices;
    return 4 * m.num_indices;
}

uint32_t Meta_get_vertex_data_size(const CG2VDMeta m)
{
    return m.num_vertices * m.vertex_size;
}

void Meta_read(CG2VDMeta &m, FILE *f)
{
    uint32_t i;
    size_t to_read, total_size;
    assert(f);

    VD_READ_VAR(m.internal_meta_size, f);
    total_size = to_read = m.internal_meta_size - sizeof(uint32_t);
    to_read -= VD_READ_VAR(m.primitive, f);
    to_read -= VD_READ_VAR(m.index_type, f);
    to_read -= VD_READ_VAR(m.num_vertices, f);
    to_read -= VD_READ_VAR(m.num_indices, f);
    uint32_t n_attribs = 0;
    to_read -= VD_READ_VAR(m.vertex_size, f);
    to_read -= VD_READ_VAR(n_attribs, f);
    assert(to_read <= total_size);
    fseek(f, static_cast<long>(to_read), SEEK_CUR);

    m.attributes.clear();

    for (i = 0; i < n_attribs; i++)
    {
        m.attributes.emplace_back();
        Attribute_read(m.attributes.back(), f);
    }
}

#undef VD_READ_VAR

void Meta_read_data(const CG2VDMeta &m,
                    void *index_data,
                    void *vertex_data,
                    FILE *f)
{
    assert(index_data);
    assert(vertex_data);
    assert(f);
    fread(index_data, Meta_get_index_data_size(m), 1, f);
    fread(vertex_data, Meta_get_vertex_data_size(m), 1, f);
}

uint32_t Attribute_size(const CG2VDAttribute &am)
{
    uint32_t tsize = 0;
    switch (am.type)
    {
    case CG2_UBYTE:
    case CG2_BYTE:
        tsize = sizeof(uint8_t);
        break;
    case CG2_USHORT:
    case CG2_HALF_FLOAT:
    case CG2_SHORT:
        tsize = sizeof(uint16_t);
        break;

    case CG2_INT:
    case CG2_UINT:
    case CG2_INT_2_10_10_10_REV:
    case CG2_UINT_2_10_10_10_REV:
        tsize = sizeof(uint32_t);
        break;

    case CG2_FLOAT:
        tsize = sizeof(float);
        break;
    case CG2_DOUBLE:
        tsize = sizeof(double);
        break;
    }

    if (am.type == CG2_INT_2_10_10_10_REV || am.type == CG2_UINT_2_10_10_10_REV)
        return tsize;

    return am.count * tsize;
}
} // namespace

bool glutil::Mesh::LoadFromCg2vd(const std::string &path)
{
}