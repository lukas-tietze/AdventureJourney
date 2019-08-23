#include "data/String.hpp"

std::string util::FormatLocalTime(const std::string &format)
{
    return FormatLocalTime(format, std::time(nullptr));
}

std::string util::FormatLocalTime(const std::string &format, std::time_t time)
{
    char buf[256];
    auto localTime = std::localtime(&time);
    auto count = std::strftime(buf, 256, format.c_str(), localTime);

    if (count == 0)
        throw util::TimeFormatException(format, time);

    return std::string(buf, count);
}