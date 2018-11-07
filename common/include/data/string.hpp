#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace util
{
std::string format(const std::string &format, ...);
std::string to_upper(const std::string &nameBuf);
std::string to_lower(const std::string &nameBuf);
void to_upper_inplace(std::string &nameBuf);
void to_lower_inplace(std::string &nameBuf);
std::vector<std::string> split(const std::string &str, bool removeEmtpyEntries = false);
std::vector<std::string> split(const std::string &str, char seperator, bool removeEmtpyEntries = false);
std::vector<std::string> split(const std::string &str, const std::string &chars, bool removeEmtpyEntries = false);
std::vector<std::string> split(const std::string &str, bool (*)(char), bool removeEmtpyEntries = false);
std::string strip(const std::string &);
std::string strip_front(const std::string &);
std::string strip_back(const std::string &);

std::string unicode_to_string(uint32_t);

template <class T>
std::string to_string(const T &arg)
{
    std::stringstream s;

    s << arg;

    return s.str();
}

template <typename NumT>
bool parse_integral(const std::string &text, NumT &target)
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
bool parse_float(const std::string &text, NumT &target)
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