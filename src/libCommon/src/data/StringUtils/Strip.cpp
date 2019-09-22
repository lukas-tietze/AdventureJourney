#include "libCommon/data/String.hpp"

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

std::string &util::StripInplace(std::string &str)
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

    str.erase(end, str.length() - end - 1);
    str.erase(0, start);

    return str;
}

std::string &util::StripFrontInplace(std::string &str)
{
    if (str.empty())
    {
        return str;
    }

    size_t start = 0;

    while (start < str.length() && std::isspace(str[start]))
        start++;

    str.erase(0, start);

    return str;
}

std::string &util::StripBackInplace(std::string &str)
{
    if (str.empty())
    {
        return str;
    }

    size_t end = str.length() - 1;

    while (end < str.length() && std::isspace(str[end]))
        end--;

    str.erase(end, str.length() - end - 1);

    return str;
}
