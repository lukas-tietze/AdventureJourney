#include "DummyData.hpp"

gui::models::Vertex_XYZ_RGB gui::models::coordData[6] =
    {
        {{1.f, 0.f, 0.f}, {255, 0, 0}},
        {{-1.f, 0.f, 0.f}, {255, 0, 0}},
        {{0.f, 1.f, 0.f}, {0, 255, 0}},
        {{0.f, -1.f, 0.f}, {0, 255, 0}},
        {{0.f, 0.f, 1.f}, {0, 0, 255}},
        {{0.f, 0.f, -1.f}, {0, 0, 255}},
};

GLubyte gui::models::coordIndices[6] = {
    0, 1, 2, 3, 4, 5};
