#include "QuadricHelper.internal.hpp"
#include "data/Math.hpp"
#include <limits>
#include "data/Io.hpp"
#include "data/IteratorUtils.hpp"

bool gui::quadrics::CreateMesh(glutil::Mesh &out, std::vector<gui::Vertex_Full> &vertices, std::vector<uint16_t> &indices)
{
    util::dbg.WriteLine("Created Quadric with % vertices and % indices.\nVertices: {%}\nIndices: %",
                        vertices.size(),
                        indices.size(),
                        util::WrapIterable(vertices.begin(), vertices.end(), "}, {"),
                        util::WrapIterable(indices.begin(), indices.end(), ", "));

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

uint16_t gui::quadrics::TexCoord(float f)
{
    return static_cast<uint16_t>(util::Crop(f, 0.f, 1.f) * static_cast<float>(std::numeric_limits<uint16_t>::max()));
}

gui::Vertex_Full &gui::quadrics::FillColor(gui::Vertex_Full &vertex, uint32_t color)
{
    vertex.color[0] = (color & 0xff000000) >> 24;
    vertex.color[1] = (color & 0x00ff0000) >> 16;
    vertex.color[2] = (color & 0x0000ff00) >> 8;
    vertex.color[3] = color & 0x000000ff;

    return vertex;
}

gui::Vertex_Full &gui::quadrics::SetPositionAndNormal(gui::Vertex_Full &vertex, float x, float y, float z)
{
    vertex.position[0] = x;
    vertex.position[1] = y;
    vertex.position[2] = z;

    vertex.normal[0] = x;
    vertex.normal[1] = y;
    vertex.normal[2] = z;

    return vertex;
}