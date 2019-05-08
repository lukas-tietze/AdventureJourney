#pragma once

#include <vector>

#include "DummyData.hpp"

namespace gui
{
glutil::Mesh CreateMesh(std::vector<gui::Vertex_Full> &vertices, std::vector<uint16_t> &indices);
uint16_t TexCoord(float f);
}