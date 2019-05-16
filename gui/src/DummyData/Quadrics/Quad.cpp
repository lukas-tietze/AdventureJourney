#include "DummyData.hpp"
#include "QuadricHelper.internal.hpp"

bool gui::quadrics::Quad(glutil::Mesh &out, uint32_t color)
{
    std::vector<gui::Vertex_Full> vertices;
    std::vector<uint16_t> indices = {0, 3, 2, 2, 1, 0};

    vertices.reserve(4);

    gui::Vertex_Full vertex;

    FillColor(vertex, color);
    vertex.normal[0] = 0;
    vertex.normal[1] = 1;
    vertex.normal[2] = 0;

    vertex.position[0] = -1;
    vertex.position[1] = 0;
    vertex.position[2] = 1;

    vertex.texture[0] = 0;
    vertex.texture[1] = 0;

    vertices.push_back(vertex);

    vertex.position[0] = 1;
    vertex.position[1] = 0;
    vertex.position[2] = 1;

    vertex.texture[0] = 1;
    vertex.texture[1] = 0;

    vertices.push_back(vertex);

    vertex.position[0] = 1;
    vertex.position[1] = 0;
    vertex.position[2] = -1;

    vertex.texture[0] = 1;
    vertex.texture[1] = 1;

    vertices.push_back(vertex);

    vertex.position[0] = -1;
    vertex.position[1] = 0;
    vertex.position[2] = -1;

    vertex.texture[0] = 0;
    vertex.texture[1] = 1;

    vertices.push_back(vertex);

    return CreateMesh(out, vertices, indices);
}