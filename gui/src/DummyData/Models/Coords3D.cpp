#include "DummyData.hpp"

#include "cmath"

namespace
{
constexpr uint resolution = 8;

gui::Vertex_XYZ_RGB vertices[3 * 2 * resolution];
GLubyte indices[3 * 6 * resolution];
glutil::Mesh mesh;
bool meshReady = false;

void BuildMesh()
{
    for (int axis = 0; axis < 3; axis++)
    {
        for (int pt = 0; pt < resolution; pt++)
        {
            for (int i = 0; i < 2; i++)
            {
                auto &vertex = vertices[axis * 2 * resolution + 2 * pt + i];
                auto rotation = glm::radians(pt * 360.f / resolution);
                vertex.position[axis] = -1.f;
                vertex.position[(axis + 1) % 3] = std::sin(rotation);
                vertex.position[(axis + 2) % 3] = std::cos(rotation);

                vertex.color[axis] = 255;
                vertex.color[(axis + 1) % 3] = 0;
                vertex.color[(axis + 2) % 3] = 0;
            }

            auto base = axis * 2 * resolution;
            auto offset = 0;
            auto id = axis * 6 * resolution + 6 * pt;

            indices[id + 0] = base + ((offset + 0) % resolution);
            indices[id + 1] = base + ((offset + 2) % resolution);
            indices[id + 2] = base + ((offset + 3) % resolution);
            indices[id + 3] = base + ((offset + 0) % resolution);
            indices[id + 4] = base + ((offset + 3) % resolution);
            indices[id + 5] = base + ((offset + 1) % resolution);
        }
    }

    mesh.LoadFromData(6, sizeof(gui::Vertex_XYZ_RGB), vertices,
                      6, GL_UNSIGNED_BYTE, indices,
                      {glutil::GeometryBufferAttribute(0, 3, GL_FLOAT, GL_FALSE, offsetof(gui::Vertex_XYZ_RGB, position)),
                       glutil::GeometryBufferAttribute(1, 3, GL_UNSIGNED_BYTE, GL_FALSE, offsetof(gui::Vertex_XYZ_RGB, color))},
                      GL_TRIANGLES);

    meshReady = true;
}
} // namespace

const glutil::Mesh &gui::models::Coord3dMesh()
{
    if (!meshReady)
        BuildMesh();

    return mesh;
}