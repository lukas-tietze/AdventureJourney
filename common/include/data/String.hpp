#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace util
{
std::string Format(const std::string &format, ...);
std::string ToUpper(const std::string &nameBuf);
std::string ToLower(const std::string &nameBuf);
void ToUpperInplace(std::string &nameBuf);
void ToLowerInplace(std::string &nameBuf);
std::vector<std::string> Split(const std::string &str, bool removeEmtpyEntries = false);
std::vector<std::string> Split(const std::string &str, char seperator, bool removeEmtpyEntries = false);
std::vector<std::string> Split(const std::string &str, const std::string &chars, bool removeEmtpyEntries = false);
std::vector<std::string> Split(const std::string &str, bool (*)(char), bool removeEmtpyEntries = false);
std::string Strip(const std::string &);
std::string StripFront(const std::string &);
std::string StripBack(const std::string &);

std::string UtfCodePointToNarrowString(uint32_t);

uint32_t Hex4ToNumber(const std::string &);
uint32_t Hex4ToNumber(const char *);
uint8_t HexToNumber(char);
uint8_t HexToNumber(char, char);
uint32_t HexToNumber(const std::string &);
uint32_t HexToNumber(const char *);
bool IsHexChar(char);

template <class T>
std::string ToString(const T &arg)
{
    std::stringstream s;

    s << arg;

    return s.str();
}

template <typename NumT>
bool ParseIntegral(const std::string &text, NumT &target)
{
    try
    {
        target = (NumT)std::stol(text);
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
    catch (const std::out_of_range &e)
    {
        return false;
    }

    return true;
}

template <typename NumT>
bool ParseFloat(const std::string &text, NumT &target)
{
    try
    {
        target = (NumT)std::stod(text);
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
    catch (const std::out_of_range &e)
    {
        return false;
    }

    return true;
}

namespace
{
void Format2Internal(const std::string &format, std::stringstream &buf, size_t pos)
{
    buf << format.c_str() + pos;
}

template <class TFirst, class... TArgs>
void Format2Internal(const std::string &format, std::stringstream &buf, size_t pos, const TFirst &firstArg, const TArgs &... args)
{
    while (pos < format.length() - 1)
    {
        if (format[pos] == '%')
        {
            buf << firstArg;
            Format2Internal(format, buf, pos + 1, args...);
            return;
        }
        else if (format[pos] == '\\')
        {
            buf << format[pos + 1];
            pos += 2;
        }
        else
        {
            buf << format[pos];
            pos++;
        }
    }

    if (format.back() == '%')
    {
        buf << firstArg;
    }
}
} // namespace

std::string Format2(const std::string &format);

template <class TFirst, class... TArgs>
std::string Format2(const std::string &format, const TFirst &firstArg, const TArgs &... args)
{
    std::stringstream buf;

    Format2Internal(format, buf, 0, firstArg, args...);

    return buf.str();
}
} // namespace util