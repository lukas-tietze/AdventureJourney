#pragma once

#include <cinttypes>
#include <cmath>

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

namespace def
{
#ifdef M_PI
constexpr double Pi = M_PI;
#else
constexpr double Pi = 3.1415926535897932384626433832795028841971693993751058209749;
#endif

constexpr double GoldenRatio = 1.6180339887498949;
constexpr double InverseGolderRatio = (1.0 / GoldenRatio);

#ifdef DEBUG
constexpr bool IsDebug = true;
#else
constexpr bool IsDebug = false;
#endif
} // namespace def
