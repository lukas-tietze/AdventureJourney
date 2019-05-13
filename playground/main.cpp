#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include "data/String.hpp"
#include "data/Io.hpp"
#include "glad/glad.h"
#include "DummyData.hpp"

namespace
{
struct vec1
{
    union {
        float x;
        float r;
    };
};

struct vec2
{
    union {
        float x;
        float r;
    };

    union {
        float y;
        float g;
    };
};

struct vec3
{
};

struct vec4
{
};
} // namespace

int main()
{
}