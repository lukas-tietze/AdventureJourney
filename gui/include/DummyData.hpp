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
    GLubyte color[4];
};

struct Vertex_XYZ_RGB_ST
{
    GLfloat position[3];
    GLubyte color[4];
    GLshort texture[2];
};

struct Vertex_XYZ_NRM_RGB
{
    GLfloat position[3];
    GLfloat normal[3];
    GLubyte color[4];
};

struct Vertex_XYZ_NRM_RGB_ST
{
    GLfloat position[3];
    GLfloat normal[3];
    GLushort texture[2];
    GLubyte color[4];
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

bool Box(glutil::Mesh &, uint32_t color = DEFAULT_COLOR);
bool Box(uint32_t slicesX, uint32_t slicesY, uint32_t slicesZ, glutil::Mesh &, uint32_t color = DEFAULT_COLOR);
bool UVSphere(uint32_t slices, uint32_t stacks, glutil::Mesh &, uint32_t color = DEFAULT_COLOR);
bool IcoSphere(uint32_t subdiv, glutil::Mesh &, uint32_t color = DEFAULT_COLOR);
bool Cylinder(uint32_t slices, uint32_t stacks, glutil::Mesh &, uint32_t color = DEFAULT_COLOR);
bool Disk(uint32_t slices, uint32_t loops, glutil::Mesh &, uint32_t color = DEFAULT_COLOR);
bool Cone(uint32_t slices, uint32_t stacks, glutil::Mesh &, uint32_t color = DEFAULT_COLOR);
bool Cone(float maxHeight, uint32_t slices, uint32_t stacks, glutil::Mesh &, uint32_t color = DEFAULT_COLOR);
} // namespace quadrics
namespace models
{
const glutil::MeshBuffer &CubeMesh();
const glutil::MeshBuffer &CoordMesh();
const glutil::MeshBuffer &Coord3dMesh();
} // namespace models
} // namespace gui