#ifndef STRING_CONVERSIONS_HPP
#define STRING_CONVERSIONS_HPP

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
} // namespace util

#endif /*STRING_CONVERSIONS_HPP*/