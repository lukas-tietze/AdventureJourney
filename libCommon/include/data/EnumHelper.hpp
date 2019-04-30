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
    ParsingException(const std::type_info &, const std::string &value);
};

template <class T>
const std::initializer_list<T> &ListValues()
{
    return std::initializer_list<T>{};
}

template <class T>
const std::string &GetEnumDescription(T value)
{
    return "";
}

template <class T>
bool TryDeserialize(const std::string &value, T &buf)
{
    std::vector<std::tuple<T, std::string>> items;

    if (items.empty())
    {
        for (const auto &item : util::ListValues<T>())
        {
            items.push_back(std::make_tuple(item, util::ToString(item)));
        }
    }

    for (const auto &item : items)
    {
        if (std::get<1>(item) == value)
        {
            buf = std::get<0>(item);
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

    throw ParsingException(typeid(T), value);
}

template <class T>
struct EnumInfo
{
    T value;
    std::string stringRepresentation;
    std::string description;
    int integerRepresentation;
};

template <class T>
EnumInfo<T> CreateEnumInfo(T value)
{
    EnumInfo<T> res;

    res.value = value;
    res.stringRepresentation = util::ToString(value);
    res.description = util::GetEnumDescription(value);
    res.integerRepresentation = static_cast<int>(value);

    return res;
}
} // namespace util
