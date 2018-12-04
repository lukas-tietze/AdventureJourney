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
} // namespace util