#include "data/String.hpp"

#include <algorithm>

std::string &util::ToLowerInplace(std::string &nameBuf)
{
    std::transform(nameBuf.begin(), nameBuf.end(), nameBuf.begin(), [](char c) -> char { return std::tolower(c); });

    return nameBuf;
}

std::string util::ToLower(const std::string &nameBuf)
{
    std::string buf(nameBuf);

    ToLowerInplace(buf);

    return buf;
}

std::string &util::ToUpperInplace(std::string &nameBuf)
{
    std::transform(nameBuf.begin(), nameBuf.end(), nameBuf.begin(), [](char c) -> char { return std::toupper(c); });

    return nameBuf;
}

std::string util::ToUpper(const std::string &nameBuf)
{
    std::string buf(nameBuf);

    util::ToUpperInplace(buf);

    return buf;
}
