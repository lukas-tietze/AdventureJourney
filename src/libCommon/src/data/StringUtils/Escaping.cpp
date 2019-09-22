#include <codecvt>
#include <iomanip>

#include "libCommon/data/String.hpp"

char util::Escape(char c)
{
    switch (c)
    {
    case 'n':
        return '\n';
    case 't':
        return '\t';
    case '?':
        return '\?';
    case 'b':
        return '\b';
    case 'a':
        return '\a';
    case 'e':
        return '\e';
    case 'f':
        return '\f';
    case 'v':
        return '\v';
    case '"':
        return '\"';
    default:
        return c;
    }
}

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
    case '\e':
        return "\\e";
    case '\f':
        return "\\f";
    case '\v':
        return "\\v";
    case '\"':
        return "\\\"";
    default:
        return std::string({c});
    }
}

std::string util::UtfCodePointToNarrowString(uint32_t codePoint)
{
    return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(codePoint);
}
