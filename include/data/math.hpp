#pragma once

#include <string>
#include <stdexcept>

namespace util
{
int hex4ToNumber(const std::string &);
int hex4ToNumber(const char *);
int hexToNumber(char);
bool is_hex_char(char);

template <class T>
T crop(const T &x, const T &min, const T &max)
{
    if (x < min)
        return min;
    else if (x > max)
        return max;
    else
        return x;
}
} // namespace util