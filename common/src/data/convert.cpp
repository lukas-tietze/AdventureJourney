#include "data/math.hpp"
#include "exception.hpp"
#include "defs.hpp"

bool util::is_hex_char(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

uint32_t util::hex4ToNumber(const std::string &data)
{
    if (data.length() >= 4)
    {
        return util::hex4ToNumber(data.c_str());
    }

    return (uint32_t)-1;
}

uint32_t util::hex4ToNumber(const char *data)
{
    return (hexToNumber(data[0]) << 12) |
           (hexToNumber(data[1]) << 8) |
           (hexToNumber(data[2]) << 4) |
           hexToNumber(data[3]);
}

uint8_t util::hexToNumber(char c)
{
    switch (c)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case 'a':
    case 'A':
        return 10;
    case 'b':
    case 'B':
        return 11;
    case 'c':
    case 'C':
        return 12;
    case 'd':
    case 'D':
        return 13;
    case 'e':
    case 'E':
        return 14;
    case 'f':
    case 'F':
        return 15;
    default:
        throw std::runtime_error("illegal value for hexadecimal digit!");
    }
}