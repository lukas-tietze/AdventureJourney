#include <stdarg.h>
#include <algorithm>

#include "data/string.hpp"

std::string util::format(const std::string &format, ...)
{
    va_list va;
    va_start(va, format);
    auto buf = (char *)std::malloc(4096);

    auto writtenLength = std::vsprintf(buf, format.c_str(), va);

    if (writtenLength > 4096)
    {
        buf = (char *)std::realloc(buf, writtenLength + 1);
        writtenLength = std::vsprintf(buf, format.c_str(), va);
    }

    va_end(va);

    std::string res(buf, writtenLength);

    std::free(buf);

    return res;
}

std::string &util::to_lower(std::string &nameBuf)
{
    std::transform(nameBuf.begin(), nameBuf.end(), nameBuf.begin(), [](char c) -> char { return std::tolower(c); });

    return nameBuf;
}

std::string util::to_lower(const std::string &nameBuf)
{
    std::string buf(nameBuf);

    to_lower(buf);

    return buf;
}

std::string &util::to_upper(std::string &nameBuf)
{
    std::transform(nameBuf.begin(), nameBuf.end(), nameBuf.begin(), [](char c) -> char { return std::toupper(c); });

    return nameBuf;
}

std::string util::to_upper(const std::string &nameBuf)
{
    std::string buf(nameBuf);

    util::to_upper(buf);

    return buf;
}

std::vector<std::string> util::split(const std::string &str)
{
    std::vector<std::string> res;
    size_t i = 0;
    size_t next = str.find(',', i);

    while (next != std::string::npos)
    {
        res.push_back(str.substr(i, next - i));
        i = next + 1;
        next = str.find(',', i);
    }

    if (i != str.length())
    {
        res.push_back(str.substr(i));
    }

    return res;
}