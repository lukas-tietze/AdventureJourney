#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>
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
    union {
        float x;
        float r;
    };

    union {
        float y;
        float g;
    };

    union {
        float z;
        float b;
    };
};

struct vec4
{
    union {
        float x;
        float r;
    };

    union {
        float y;
        float g;
    };

    union {
        float z;
        float b;
    };

    union {
        float w;
        float a;
    };
};
} // namespace

int main()
{
    std::printf("Golder Schnitt = %1.16lf", ((1.0 + std::sqrt(5.0)) / 2.0));
}