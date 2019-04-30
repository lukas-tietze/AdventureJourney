#include "data/String.hpp"

std::vector<std::string> &util::Split(const std::string &str, std::vector<std::string> &buf, char seperator, bool removeEmtpyEntries)
{
    buf.clear();
    size_t i = 0;
    size_t next = str.find(seperator, i);

    while (next != std::string::npos)
    {
        if (!removeEmtpyEntries || next - i > 0)
        {
            buf.push_back(str.substr(i, next - i));
        }

        i = next + 1;
        next = str.find(seperator, i);
    }

    if (i != str.length())
    {
        buf.push_back(str.substr(i));
    }

    return buf;
}

std::vector<std::string> &util::Split(const std::string &str, std::vector<std::string> &buf, const std::string &chars, bool removeEmtpyEntries)
{
    buf.clear();
    size_t i = 0;
    size_t next = str.find_first_of(chars, i);

    while (next != std::string::npos)
    {
        if (!removeEmtpyEntries || next - i > 0)
        {
            buf.push_back(str.substr(i, next - i));
        }

        i = next + 1;
        next = str.find_first_of(chars, i);
    }

    if (i != str.length())
    {
        buf.push_back(str.substr(i));
    }

    return buf;
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

std::vector<std::string> &util::Split(const std::string &str, std::vector<std::string> &buf, bool (*func)(char), bool removeEmtpyEntries)
{
    buf.clear();

    size_t i = 0;
    size_t next = find(str, func, 0);

    while (next != std::string::npos)
    {
        if (!removeEmtpyEntries || next - i > 0)
        {
            buf.push_back(str.substr(i, next - i));
        }

        i = next + 1;
        next = find(str, func, i);
    }

    if (i != str.length())
    {
        buf.push_back(str.substr(i));
    }

    return buf;
}

std::vector<std::string> &util::Split(const std::string &str, std::vector<std::string> &buf, bool removeEmtpyEntries)
{
    buf.clear();
    return util::Split(str, buf, ' ', removeEmtpyEntries);
}

std::vector<std::string> util::Split(const std::string &str, bool removeEmtpyEntries)
{
    std::vector<std::string> buf;

    util::Split(str, buf, removeEmtpyEntries);

    return buf;
}
std::vector<std::string> util::Split(const std::string &str, char seperator, bool removeEmtpyEntries)
{
    std::vector<std::string> buf;

    util::Split(str, buf, seperator, removeEmtpyEntries);

    return buf;
}
std::vector<std::string> util::Split(const std::string &str, const std::string &chars, bool removeEmtpyEntries)
{
    std::vector<std::string> buf;

    util::Split(str, buf, chars, removeEmtpyEntries);

    return buf;
}
std::vector<std::string> util::Split(const std::string &str, bool (*f)(char), bool removeEmtpyEntries)
{
    std::vector<std::string> buf;

    util::Split(str, buf, f, removeEmtpyEntries);

    return buf;
}
