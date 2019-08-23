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

template<class NumT>
bool util::ParseIntegral(const std::string &text, NumT &target)
{
    try
    {
        target = static_cast<NumT>(std::stol(text));
    }
    catch (...)
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
    catch (...)
    {
        return false;
    }

    return true;
}
