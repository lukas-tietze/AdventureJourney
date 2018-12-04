#pragma once

#include <string>
#include <stdexcept>

namespace util
{
uint32_t Hex4ToNumber(const std::string &);
uint32_t Hex4ToNumber(const char *);
uint8_t HexToNumber(char);
bool IsHexChar(char);

template <class T>
T Crop(const T &x, const T &min, const T &max)
{
    if (x < min)
        return min;
    else if (x > max)
        return max;
    else
        return x;
}
} // namespace util