#pragma once

#include "glad/glad.h"

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
#pragma pack(pop)

extern Vertex_XYZ_RGB cubeData[8];
extern GLubyte cubeIndices[36];

extern Vertex_XYZ_RGB coordData[6];
extern GLubyte coordIndices[6];
} // namespace models
} // namespace gui