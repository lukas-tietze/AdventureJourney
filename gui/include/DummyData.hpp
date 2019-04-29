#pragma once

#include "glad/glad.h"
#include "Objects.hpp"

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

typedef Vertex_XYZ_NRM_RGB_ST Vertex_Full;
#pragma pack(pop)

const glutil::Mesh &CubeMesh();
const glutil::Mesh &CoordMesh();
const glutil::Mesh &Coord3dMesh();
} // namespace models
} // namespace gui