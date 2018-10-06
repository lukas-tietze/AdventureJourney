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

void util::to_lower(std::string &nameBuf)
{
    std::transform(nameBuf.begin(), nameBuf.end(), nameBuf.begin(), [](char c) -> char { return std::tolower(c); });
}

std::string util::to_lower(const std::string &nameBuf)
{
    std::string buf(nameBuf);

    to_lower(buf);

    return buf;
}

void util::to_upper(std::string &nameBuf)
{
    std::transform(nameBuf.begin(), nameBuf.end(), nameBuf.begin(), [](char c) -> char { return std::toupper(c); });
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

std::string util::strip(const std::string &str)
{
    if (str.empty())
    {
        return str;
    }

    size_t start = 0;
    size_t end = str.length() - 1;

    while (start < str.length() && std::isspace(str[start]))
        start++;

    while (end >= 0 && std::isspace(str[end]))
        end--;

    return str.substr(start, end);
}

std::string util::strip_front(const std::string &str)
{
    if (str.empty())
    {
        return str;
    }

    size_t start = 0;

    while (start < str.length() && std::isspace(str[start]))
        start++;

    return str.substr(start);
}

std::string util::strip_back(const std::string &str)
{
    if (str.empty())
    {
        return str;
    }

    size_t end = str.length() - 1;

    while (end >= 0 && std::isspace(str[end]))
        end--;

    return str.substr(0, end);
}

void util::strip(std::string &str)
{
    if (str.empty())
    {
        return;
    }

    size_t start = 0;
    size_t end = str.length() - 1;

    while (start < str.length() && std::isspace(str[start]))
        start++;

    while (end >= 0 && std::isspace(str[end]))
        end--;

    str.assign(str.substr(start, end));
}

void util::strip_front(std::string &str)
{
    if (str.empty())
    {
        return;
    }

    size_t start = 0;

    while (start < str.length() && std::isspace(str[start]))
        start++;

    str.assign(str.substr(start));
}

void util::strip_back(std::string &str)
{
    if (str.empty())
    {
        return;
    }

    size_t end = str.length() - 1;

    while (end >= 0 && std::isspace(str[end]))
        end--;

    str.assign(str.substr(0, end));
}