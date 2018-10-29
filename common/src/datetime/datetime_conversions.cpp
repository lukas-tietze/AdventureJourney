#include <ctime>

#include "defs.hpp"
#include "datetime/datetime_conversions.hpp"

double util::clock_to_ms(clock_t clocks)
{
    return clocks / (double)(CLOCKS_PER_SEC / 1000);
}

double util::clock_to_seconds(clock_t clocks)
{
    return clocks / (double)CLOCKS_PER_SEC;
}