#pragma once

#include <iostream>

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
    GLshort texture[2];
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
    GLushort texture[2];
    GLubyte color[3];
};
#pragma pack(pop)

typedef Vertex_XYZ_NRM_RGB_ST Vertex_Full;

std::ostream &operator<<(std::ostream &, const Vertex_XYZ &);
std::ostream &operator<<(std::ostream &, const Vertex_XYZ_RGB &);
std::ostream &operator<<(std::ostream &, const Vertex_XYZ_RGB_ST &);
std::ostream &operator<<(std::ostream &, const Vertex_XYZ_NRM_RGB &);
std::ostream &operator<<(std::ostream &, const Vertex_XYZ_NRM_RGB_ST &);

namespace quadrics
{
constexpr uint32_t DEFAULT_COLOR = 0x808080ff;

glutil::Mesh Box(uint32_t color = DEFAULT_COLOR);
glutil::Mesh Box(int slicesX, int slicesY, int slicesZ, uint32_t color = DEFAULT_COLOR);
glutil::Mesh UVSphere(int slices, int stacks, uint32_t color = DEFAULT_COLOR);
glutil::Mesh IcoSphere(int subdiv, uint32_t color = DEFAULT_COLOR);
glutil::Mesh Cylinder(int slices, int stacks, uint32_t color = DEFAULT_COLOR);
glutil::Mesh Disk(int slices, int loops, uint32_t color = DEFAULT_COLOR);
glutil::Mesh Cone(int slices, int stacks, uint32_t color = DEFAULT_COLOR);
glutil::Mesh Cone(float maxHeight, int slices, int stacks, uint32_t color = DEFAULT_COLOR);
} // namespace quadrics
namespace models
{
const glutil::Mesh &CubeMesh();
const glutil::Mesh &CoordMesh();
const glutil::Mesh &Coord3dMesh();
} // namespace models
} // namespace gui