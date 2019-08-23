#include <ctime>

#include "datetime/Conversions.hpp"

double util::ClockToMs(clock_t clocks)
{
    return clocks / (double)(CLOCKS_PER_SEC / 1000);
}

double util::ClockToSeconds(clock_t clocks)
{
    return clocks / (double)CLOCKS_PER_SEC;
}