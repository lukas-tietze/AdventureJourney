#include "data/String.hpp"

bool util::EndsWith(const std::string &str, const std::string &end)
{
    if (end.empty())
        return true;

    if (str.length() < end.length())
        return false;

    const size_t offset = str.length() - end.length();
    const size_t max = end.length();
    size_t i = 0;

    while (i < max && end[i] == str[offset + i])
        i++;

    return i == max;
}

bool util::StartsWith(const std::string &str, const std::string &start)
{
    if (start.empty())
        return true;

    if (str.length() < start.length())
        return false;

    const size_t max = start.length();
    size_t i = 0;

    while (i < max && start[i] == str[i])
        i++;

    return i == max;
}
