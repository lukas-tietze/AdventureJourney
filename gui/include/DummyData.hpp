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
struct QuadricConfig
{
    glm::vec2 texCoordOffset = glm::vec2(0.f, 0.f);
    glm::vec2 texCoordScale = glm::vec2(0.f, 0.f);
    bool useColorFunc = false;
    union {
        uint32_t (*colorFunc)(const glm::vec3 &);
        uint32_t color = 0x808080ff;
    };
};

bool Quad(glutil::Mesh &, const QuadricConfig &);
bool Quad(glutil::Mesh &);
bool Box(glutil::Mesh &, const QuadricConfig &);
bool Box(glutil::Mesh &);
bool Box(uint32_t slicesX, uint32_t slicesY, uint32_t slicesZ, glutil::Mesh &, const QuadricConfig &);
bool Box(uint32_t slicesX, uint32_t slicesY, uint32_t slicesZ, glutil::Mesh &);
bool UVSphere(uint32_t slices, uint32_t stacks, glutil::Mesh &, const QuadricConfig &);
bool UVSphere(uint32_t slices, uint32_t stacks, glutil::Mesh &);
bool IcoSphere(uint32_t subdiv, glutil::Mesh &, const QuadricConfig &);
bool IcoSphere(uint32_t subdiv, glutil::Mesh &);
bool Cylinder(uint32_t slices, uint32_t stacks, glutil::Mesh &, const QuadricConfig &);
bool Cylinder(uint32_t slices, uint32_t stacks, glutil::Mesh &);
bool Disk(uint32_t slices, uint32_t loops, glutil::Mesh &, const QuadricConfig &);
bool Disk(uint32_t slices, uint32_t loops, glutil::Mesh &);
bool Cone(uint32_t slices, uint32_t stacks, glutil::Mesh &, const QuadricConfig &);
bool Cone(uint32_t slices, uint32_t stacks, glutil::Mesh &);
bool Cone(float maxHeight, uint32_t slices, uint32_t stacks, glutil::Mesh &, const QuadricConfig &);
bool Cone(float maxHeight, uint32_t slices, uint32_t stacks, glutil::Mesh &);
} // namespace quadrics
namespace models
{
const glutil::MeshBuffer &CubeMesh();
const glutil::MeshBuffer &CoordMesh();
const glutil::MeshBuffer &Coord3dMesh();
} // namespace models
} // namespace gui