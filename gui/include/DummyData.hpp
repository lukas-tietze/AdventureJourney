#pragma once

#include "glad/glad.h"
#include "Objects.hpp"
#include "Defs.hpp"

namespace gui
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

namespace quadrics
{
glutil::Mesh Box(VertexElements requiredElements);
glutil::Mesh Box(int slicesX, int slicesY, int slicesZ, VertexElements requiredElements);
glutil::Mesh UVSphere(int slices, int stacks, VertexElements requiredElements);
glutil::Mesh IcoSphere(int subdiv, VertexElements requiredElements);
glutil::Mesh Cylinder(int slices, int stacks, VertexElements requiredElements);
glutil::Mesh Disk(int slices, int loops, VertexElements requiredElements);
glutil::Mesh Cone(int slices, int stacks, VertexElements requiredElements);
glutil::Mesh Cone(float maxHeight, int slices, int stacks, VertexElements requiredElements);
} // namespace quadrics
namespace models
{
const glutil::Mesh &CubeMesh();
const glutil::Mesh &CoordMesh();
const glutil::Mesh &Coord3dMesh();
} // namespace models
} // namespace gui