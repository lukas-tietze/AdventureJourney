#define __STDC_WANT_LIB_EXT1__ 1

#include <time.h>

#include "libCommon/data/String.hpp"

std::ostream &util::conversions::operator<<(std::ostream &s, const std::time_t &t)
{
    char buf[128];

    if(ctime_s(buf, 128, &t) == 0) {
        s << buf;
    }

    return s;
}