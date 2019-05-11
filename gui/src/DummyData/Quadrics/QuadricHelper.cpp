#include "QuadricHelper.internal.hpp"
#include "data/Math.hpp"
#include "limits"

bool gui::CreateMesh(glutil::Mesh &out, std::vector<gui::Vertex_Full> &vertices, std::vector<uint16_t> &indices)
{
    out.LoadFromData(vertices.size(), sizeof(gui::Vertex_Full), vertices.data(),
                     indices.size(), GL_UNSIGNED_SHORT, indices.data(),
                     {
                         glutil::MeshAttribute(0, 3, GL_FLOAT, false, offsetof(gui::Vertex_Full, gui::Vertex_Full::position)),
                         glutil::MeshAttribute(1, 3, GL_FLOAT, false, offsetof(gui::Vertex_Full, gui::Vertex_Full::normal)),
                         glutil::MeshAttribute(2, 4, GL_UNSIGNED_BYTE, true, offsetof(gui::Vertex_Full, gui::Vertex_Full::color)),
                         glutil::MeshAttribute(3, 2, GL_UNSIGNED_SHORT, true, offsetof(gui::Vertex_Full, gui::Vertex_Full::texture)),
                     },
                     GL_TRIANGLES, true);

    return true;
}

uint16_t gui::TexCoord(float f)
{
    return static_cast<uint16_t>(util::Crop(f, 0.f, 1.f) * static_cast<float>(std::numeric_limits<uint16_t>::max()));
}