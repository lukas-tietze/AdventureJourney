#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include "data/String.hpp"
#include "data/Io.hpp"
#include "glad/glad.h"
#include "DummyData.hpp"

int main()
{
    util::out.WriteLine("size=%, position=%, normal=%, color=%, texture=%",
                        sizeof(gui::Vertex_Full),
                        offsetof(gui::Vertex_Full, gui::Vertex_Full::position),
                        offsetof(gui::Vertex_Full, gui::Vertex_Full::normal),
                        offsetof(gui::Vertex_Full, gui::Vertex_Full::texture),
                        offsetof(gui::Vertex_Full, gui::Vertex_Full::color));
}