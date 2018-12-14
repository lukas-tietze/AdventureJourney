#pragma once

#include <cinttypes>

typedef uint32_t uint;
typedef uint64_t ulong;
typedef float math_t;
// typedef int id_t;

#define CPL_LOCATION (util::format("in <%s> (at %s:%i)", __PRETTY_FUNCTION__, __FILE__, __LINE__))