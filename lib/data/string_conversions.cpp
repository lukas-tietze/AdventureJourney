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

void util::to_lower_inplace(std::string &nameBuf)
{
    std::transform(nameBuf.begin(), nameBuf.end(), nameBuf.begin(), [](char c) -> char { return std::tolower(c); });
}

std::string util::to_lower(const std::string &nameBuf)
{
    std::string buf(nameBuf);

    to_lower_inplace(buf);

    return buf;
}

void util::to_upper_inplace(std::string &nameBuf)
{
    std::transform(nameBuf.begin(), nameBuf.end(), nameBuf.begin(), [](char c) -> char { return std::toupper(c); });
}

std::string util::to_upper(const std::string &nameBuf)
{
    std::string buf(nameBuf);

    util::to_upper_inplace(buf);

    return buf;
}

std::vector<std::string> util::split(const std::string &str, char seperator, bool removeEmtpyEntries)
{
    std::vector<std::string> res;
    size_t i = 0;
    size_t next = str.find(seperator, i);

    while (next != std::string::npos)
    {
        if (!removeEmtpyEntries || next - i > 0)
        {
            res.push_back(str.substr(i, next - i));
        }

        i = next + 1;
        next = str.find(seperator, i);
    }

    if (i != str.length())
    {
        res.push_back(str.substr(i));
    }

    return res;
}

std::vector<std::string> util::split(const std::string &str, const std::string &chars, bool removeEmtpyEntries)
{
    std::vector<std::string> res;
    size_t i = 0;
    size_t next = str.find_first_of(chars, i);

    while (next != std::string::npos)
    {
        if (!removeEmtpyEntries || next - i > 0)
        {
            res.push_back(str.substr(i, next - i));
        }

        i = next + 1;
        next = str.find_first_of(chars, i);
    }

    if (i != str.length())
    {
        res.push_back(str.substr(i));
    }

    return res;
}

namespace
{
size_t find(const std::string &str, bool (*func)(char), size_t start)
{
    auto i = start;

    while (i < str.length() && !func(str[i]))
        i++;

    return i;
}
} // namespace

std::vector<std::string> util::split(const std::string &str, bool (*func)(char), bool removeEmtpyEntries)
{
    std::vector<std::string> res;
    size_t i = 0;
    size_t next = find(str, func, 0);

    while (next != std::string::npos)
    {
        if (!removeEmtpyEntries || next - i > 0)
        {
            res.push_back(str.substr(i, next - i));
        }

        i = next + 1;
        next = find(str, func, i);
    }

    if (i != str.length())
    {
        res.push_back(str.substr(i));
    }

    return res;
}

std::vector<std::string> util::split(const std::string &str, bool removeEmtpyEntries)
{
    return util::split(str, ' ', removeEmtpyEntries);
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

    return str.substr(start, end - start + 1);
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

    return str.substr(0, end + 1);
}