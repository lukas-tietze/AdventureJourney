#include "data.hpp"

int util::hex4ToNumber(const char *data)
{
    return (hexToNumber(data[0]) << 24) &
           (hexToNumber(data[1]) << 16) &
           (hexToNumber(data[2]) << 8) &
           hexToNumber(data[3]);
}

int util::hexToNumber(char c)
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
    }
}

double util::clock_to_ms(clock_t clocks)
{
    return clocks / (double)(CLOCKS_PER_SEC / 1000);
}