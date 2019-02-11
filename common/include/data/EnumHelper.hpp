#pragma once

#include <string>
#include <vector>
#include <tuple>

#include "data/String.hpp"

namespace util
{
class ParsingException : public util::Exception
{
  public:
    template <class T>
    ParsingException(const std::string &value) : Exception(util::Format("Failed to parse %: % is no valid value!", typeid(T).name(), value))
    {
    }
};

template <class T>
std::initializer_list<T> ListValues()
{
    return std::initializer_list<T>{};
}

template <class T>
bool TryDeserialize(const std::string &value, T &buf)
{
    std::vector<std::tuple<T, std::string>> items;

    if (items.empty())
    {
        for(const auto &item in util::ListValues<T>()
        {
            items.push_back(std::make_tuple(item, std::ToString(item)));
        }
    }

    for (const auto &item : items)
    {
        if (std::get<1>(*item) == value)
        {
            buf = std::get<1>(*item);
            return true;
        }
    }

    return false;
}

template <class T>
T Deserialize(const std::string &value)
{
    T res;

    if (TryDeserialize<T>(value, res))
        return res;

    throw ParsingException<T>(value);
}
} // namespace util
