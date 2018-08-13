#include "data.hpp"

#include <stdarg.h>

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