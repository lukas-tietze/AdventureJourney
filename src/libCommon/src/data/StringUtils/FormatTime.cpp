#define __STDC_WANT_LIB_EXT1__ 1

#include <ctime>

#include "libCommon/data/String.hpp"

std::string util::FormatLocalTime(const std::string &format)
{
    return FormatLocalTime(format, std::time(nullptr));
}

std::string util::FormatLocalTime(const std::string &format, std::time_t time)
{
    char buf[256];
    struct tm localTime;
    localtime_s(&time, &localTime);
    auto count = strftime(buf, 256, format.c_str(), &localTime);

    if (count == 0)
        throw util::TimeFormatException(format, time);

    return std::string(buf, count);
}