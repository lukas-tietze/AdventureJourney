#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace util
{
std::string format(const std::string &format, ...);
std::string &to_lower(std::string &nameBuf);
std::string to_lower(const std::string &nameBuf);
std::string &to_upper(std::string &nameBuf);
std::string to_upper(const std::string &nameBuf);
std::vector<std::string> split(const std::string &str);
std::vector<std::string> split(const std::string &str, char seperator);
std::vector<std::string> split(const std::string &str, char seperator[]);

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