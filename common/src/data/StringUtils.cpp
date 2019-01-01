#include <stdarg.h>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <iomanip>

#include "data/String.hpp"

std::string util::Format2(const std::string &format)
{
    return format;
}

std::string util::Format(const std::string &format, ...)
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

void util::ToLowerInplace(std::string &nameBuf)
{
    std::transform(nameBuf.begin(), nameBuf.end(), nameBuf.begin(), [](char c) -> char { return std::tolower(c); });
}

std::string util::ToLower(const std::string &nameBuf)
{
    std::string buf(nameBuf);

    ToLowerInplace(buf);

    return buf;
}

void util::ToUpperInplace(std::string &nameBuf)
{
    std::transform(nameBuf.begin(), nameBuf.end(), nameBuf.begin(), [](char c) -> char { return std::toupper(c); });
}

std::string util::ToUpper(const std::string &nameBuf)
{
    std::string buf(nameBuf);

    util::ToUpperInplace(buf);

    return buf;
}

std::vector<std::string> util::Split(const std::string &str, char seperator, bool removeEmtpyEntries)
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

std::vector<std::string> util::Split(const std::string &str, const std::string &chars, bool removeEmtpyEntries)
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

std::vector<std::string> util::Split(const std::string &str, bool (*func)(char), bool removeEmtpyEntries)
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

std::vector<std::string> util::Split(const std::string &str, bool removeEmtpyEntries)
{
    return util::Split(str, ' ', removeEmtpyEntries);
}

std::string util::Strip(const std::string &str)
{
    if (str.empty())
    {
        return str;
    }

    size_t start = 0;
    size_t end = str.length() - 1;

    while (start < str.length() && std::isspace(str[start]))
        start++;

    while (end >= start && end < str.length() && std::isspace(str[end]))
        end--;

    return str.substr(start, end - start + 1);
}

std::string util::StripFront(const std::string &str)
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

std::string util::StripBack(const std::string &str)
{
    if (str.empty())
    {
        return str;
    }

    size_t end = str.length() - 1;

    while (end < str.length() && std::isspace(str[end]))
        end--;

    return str.substr(0, end + 1);
}

std::string util::UtfCodePointToNarrowString(uint32_t codePoint)
{
    return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(codePoint);
}