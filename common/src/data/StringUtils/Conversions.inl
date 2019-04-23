#include "data/String.hpp"

template <class T>
std::string util::ToString(const T &arg)
{
    std::stringstream s;

    s << arg;

    return s.str();
}

template <class T>
T util::Parse(const std::string &value)
{
    return T();
}

template <typename NumT>
bool util::ParseIntegral(const std::string &text, NumT &target)
{
    try
    {
        target = static_cast<NumT>(std::stol(text));
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
bool util::ParseFloat(const std::string &text, NumT &target)
{
    try
    {
        target = static_cast<NumT>(std::stod(text));
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
