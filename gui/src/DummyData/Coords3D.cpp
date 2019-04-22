#include "DummyData.hpp"

namespace
{
gui::models::Vertex_XYZ_RGB vertices[6] = {
    {{1.f, 0.f, 0.f}, {255, 0, 0}},
    {{-1.f, 0.f, 0.f}, {255, 0, 0}},
    {{0.f, 1.f, 0.f}, {0, 255, 0}},
    {{0.f, -1.f, 0.f}, {0, 255, 0}},
    {{0.f, 0.f, 1.f}, {0, 0, 255}},
    {{0.f, 0.f, -1.f}, {0, 0, 255}},
};

GLubyte indices[6] = {
    0, 1, 2, 3, 4, 5};

glutil::Mesh mesh;
bool meshReady = false;

void BuildMesh()
{
    mesh.LoadFromData(6, sizeof(gui::models::Vertex_XYZ_RGB), vertices,
                      6, sizeof(GLubyte), indices,
                      {glutil::GeometryBufferAttribute(0, 3, GL_FLOAT, GL_FALSE, offsetof(gui::models::Vertex_XYZ_RGB, position)),
                       glutil::GeometryBufferAttribute(1, 3, GL_UNSIGNED_BYTE, GL_FALSE, offsetof(gui::models::Vertex_XYZ_RGB, color))});

    meshReady = true;
}
} // namespace

const glutil::Mesh &gui::models::Coord3dMesh()
{
    if (!meshReady)
        BuildMesh();

    return mesh;
}