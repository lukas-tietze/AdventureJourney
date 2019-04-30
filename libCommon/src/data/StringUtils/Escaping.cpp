#include <codecvt>
#include <iomanip>

#include "data/String.hpp"

std::string util::Unescape(char c)
{
    switch (c)
    {
    case '\n':
        return "\\n";
    case '\t':
        return "\\t";
    case '\?':
        return "\\?";
    case '\b':
        return "\\b";
    case '\a':
        return "\\a";
    default:
        return std::string(1, c);
    }
}

std::string util::UtfCodePointToNarrowString(uint32_t codePoint)
{
    return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(codePoint);
}
