#pragma once

#include "glad/glad.h"
#include "Objects.hpp"
#include "Defs.hpp"

namespace gui
{
namespace models
{
#pragma pack(push, 1)
struct Vertex_XYZ
{
    GLfloat position[3];
};

struct Vertex_XYZ_RGB
{
    GLfloat position[3];
    GLubyte color[3];
};

struct Vertex_XYZ_RGB_ST
{
    GLfloat position[3];
    GLubyte color[3];
    GLfloat texture[2];
};

struct Vertex_XYZ_NRM_RGB
{
    GLfloat position[3];
    GLfloat normal[3];
    GLubyte color[3];
};

struct Vertex_XYZ_NRM_RGB_ST
{
    GLfloat position[3];
    GLfloat normal[3];
    GLubyte color[3];
    GLfloat texture[2];
};
#pragma pack(pop)

typedef Vertex_XYZ_NRM_RGB_ST Vertex_Full;

enum class VertexElements
{
    Position = BIT(0),
    Normal = BIT(1),
    Texture = BIT(2),
    Color = BIT(3),
};

const glutil::Mesh &CubeMesh();
const glutil::Mesh &CoordMesh();
const glutil::Mesh &Coord3dMesh();

glutil::Mesh GenerateCube(VertexElements elements);
glutil::Mesh GenerateCylinder(int segments, VertexElements elements);
glutil::Mesh GenerateUvSphere(int u, int v, VertexElements elements);
glutil::Mesh GenerateIsoSphere(int sub, VertexElements elements);
} // namespace models
} // namespace gui