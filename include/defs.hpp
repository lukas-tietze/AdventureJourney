#pragma once

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned int id_t;
typedef float math_t;

#define CPL_LOCATION (util::format("in <%s> (at %s:%i)", __PRETTY_FUNCTION__, __FILE__, __LINE__))