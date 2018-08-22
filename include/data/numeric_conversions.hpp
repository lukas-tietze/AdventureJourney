#ifndef NUMERIC_CONVERSIONS_HPP
#define NUMERIC_CONVERSIONS_HPP

#include <string>
#include <stdexcept>

namespace util
{
int hex4ToNumber(const char *);

int hexToNumber(char);

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

#endif /*NUMERIC_CONVERSIONS_HPP*/