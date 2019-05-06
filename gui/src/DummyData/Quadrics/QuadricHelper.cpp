#include "QuadricHelper.internal.hpp"

glutil::Mesh gui::CreateMesh(std::vector<gui::Vertex_Full> &vertices, std::vector<uint16_t> &indices)
{
    glutil::Mesh res;

    res.LoadFromData(vertices.size(), sizeof(gui::Vertex_Full), vertices.data(),
                     indices.size(), GL_UNSIGNED_SHORT, indices.data(),
                     {
                         glutil::GeometryBufferAttribute(0, 3, GL_FLOAT, false, 0),
                         glutil::GeometryBufferAttribute(1, 3, GL_FLOAT, false, 3 * sizeof(GLfloat)),
                         glutil::GeometryBufferAttribute(2, 3, GL_UNSIGNED_BYTE, false, 6 * sizeof(GLfloat)),
                         glutil::GeometryBufferAttribute(3, 2, GL_FLOAT, false, 6 * sizeof(GLfloat) + 3 * sizeof(GLubyte)),
                     },
                     GL_TRIANGLES);
}