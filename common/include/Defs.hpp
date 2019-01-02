#pragma once

#include <cinttypes>

typedef uint32_t uint;
typedef uint64_t ulong;
typedef float math_t;
typedef __id_t id_t;

#define BIT(i) (1 << i)

#define CPL_LOCATION (util::Format("in <%s> (at %s:%i)", __PRETTY_FUNCTION__, __FILE__, __LINE__))