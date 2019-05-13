#pragma once

#include <vector>

#include "DummyData.hpp"

namespace gui
{
namespace quadrics
{
bool CreateMesh(glutil::Mesh &out, std::vector<gui::Vertex_Full> &vertices, std::vector<uint16_t> &indices);
uint16_t TexCoord(float f);
gui::Vertex_Full &FillColor(gui::Vertex_Full &, uint32_t color);
gui::Vertex_Full &SetPositionAndNormal(gui::Vertex_Full &, float x, float y, float z);
} // namespace quadrics
} // namespace gui