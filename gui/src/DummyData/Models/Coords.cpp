#include "DummyData.hpp"

namespace
{
gui::Vertex_XYZ_RGB vertices[6] = {
    {{1.f, 0.f, 0.f}, {255, 0, 0}},
    {{-1.f, 0.f, 0.f}, {255, 0, 0}},
    {{0.f, 1.f, 0.f}, {0, 255, 0}},
    {{0.f, -1.f, 0.f}, {0, 255, 0}},
    {{0.f, 0.f, 1.f}, {0, 0, 255}},
    {{0.f, 0.f, -1.f}, {0, 0, 255}},
};

GLubyte indices[6] = {
    0, 1, 2, 3, 4, 5};

glutil::MeshBuffer mesh;
bool meshReady = false;

void BuildMesh()
{
    mesh.LoadFromData(6, sizeof(gui::Vertex_XYZ_RGB), vertices,
                      6, GL_UNSIGNED_BYTE, indices,
                      {glutil::MeshAttribute(0, 3, GL_FLOAT, GL_FALSE, offsetof(gui::Vertex_XYZ_RGB, position)),
                       glutil::MeshAttribute(2, 3, GL_UNSIGNED_BYTE, GL_FALSE, offsetof(gui::Vertex_XYZ_RGB, color))},
                      GL_LINES);

    meshReady = true;
}
} // namespace

const glutil::MeshBuffer &gui::models::CoordMesh()
{
    if (!meshReady)
        BuildMesh();

    return mesh;
}