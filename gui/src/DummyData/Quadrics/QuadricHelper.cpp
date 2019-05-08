#include "QuadricHelper.internal.hpp"
#include "data/Math.hpp"
#include "limits"

glutil::Mesh gui::CreateMesh(std::vector<gui::Vertex_Full> &vertices, std::vector<uint16_t> &indices)
{
    glutil::Mesh res;

    res.LoadFromData(vertices.size(), sizeof(gui::Vertex_Full), vertices.data(),
                     indices.size(), GL_UNSIGNED_SHORT, indices.data(),
                     {
                         glutil::GeometryBufferAttribute(0, 3, GL_FLOAT, false, offsetof(gui::Vertex_Full, gui::Vertex_Full::position)),
                         glutil::GeometryBufferAttribute(1, 3, GL_FLOAT, false, offsetof(gui::Vertex_Full, gui::Vertex_Full::normal)),
                         glutil::GeometryBufferAttribute(2, 3, GL_UNSIGNED_BYTE, true, offsetof(gui::Vertex_Full, gui::Vertex_Full::color)),
                         glutil::GeometryBufferAttribute(3, 2, GL_UNSIGNED_SHORT, true, offsetof(gui::Vertex_Full, gui::Vertex_Full::texture)),
                     },
                     GL_TRIANGLES, true);

    return res;
}

uint16_t gui::TexCoord(float f)
{
    return util::Crop(f, 0.f, 1.f) * std::numeric_limits<uint16_t>::max();
}