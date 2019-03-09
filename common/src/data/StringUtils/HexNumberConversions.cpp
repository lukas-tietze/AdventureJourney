#include "data/String.hpp"
#include "Exception.hpp"
#include "Defs.hpp"

bool util::IsHexChar(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

uint32_t util::Hex4ToNumber(const std::string &data)
{
    if (data.length() >= 4)
    {
        return util::Hex4ToNumber(data.c_str());
    }

    return (uint32_t)-1;
}

uint32_t util::Hex4ToNumber(const char *data)
{
    return (HexToNumber(data[0]) << 12) |
           (HexToNumber(data[1]) << 8) |
           (HexToNumber(data[2]) << 4) |
           HexToNumber(data[3]);
}

uint8_t util::HexToNumber(char c)
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
        throw util::InvalidCaseException("illegal value for hexadecimal digit!");
    }
}

uint8_t util::HexToNumber(char high, char low)
{
    return (HexToNumber(high) << 4) | HexToNumber(low);
}

uint32_t util::HexToNumber(const std::string &str)
{
    uint32_t res = 0;

    for (size_t i = 0; i < str.length() && i < sizeof(uint32_t) * 2; i++)
    {
        res |= HexToNumber(str[i]) << (i * 4);
    }

    return res;
}

uint32_t util::HexToNumber(const char *str)
{
    uint32_t res = 0;
    size_t i = 0;

    while (*str != '\0' && i < sizeof(uint32_t) * 2)
    {
        res = (res << 4) | HexToNumber(*str);

        str++;
        i++;
    }

    return res;
}