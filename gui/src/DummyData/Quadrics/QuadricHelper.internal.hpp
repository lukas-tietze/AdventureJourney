#pragma once

#include <vector>

#include "DummyData.hpp"

namespace gui
{
namespace quadrics
{
bool CreateMesh(glutil::Mesh &out, std::vector<gui::Vertex_Full> &vertices, std::vector<uint16_t> &indices);
uint16_t TexCoord(float f);
} // namespace quadrics
} // namespace gui