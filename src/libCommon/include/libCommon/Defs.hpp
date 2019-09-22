#pragma once

#include <cinttypes>

typedef uint32_t uint;
typedef uint64_t ulong;
typedef float math_t;
typedef uint32_t id_t;

#ifndef BIT
#define BIT(i) (1 << i)
#endif

#ifndef CPL_LOCATION
#define CPL_LOCATION (util::Format("in <%s> (at %s:%i)", __PRETTY_FUNCTION__, __FILE__, __LINE__))
#endif

////PI
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028841971693993751058209749
#endif

////Goldener Schnitt, (1 + sqrt(5)) / 2
#ifndef M_GR
#define M_GR 1.6180339887498949
#endif

////Inverser Goldener Schnitt, 1 / M_GR
#ifndef M_INV_GR
#define M_INV_GR (1.0 / 1.6180339887498949)
#endif