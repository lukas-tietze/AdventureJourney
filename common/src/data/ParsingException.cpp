#include "data/EnumHelper.hpp"

util::ParsingException::ParsingException(const std::type_info &type, const std::string &value)
    : Exception(util::Format("Failed to parse %: % is no valid value!", type.name(), value))
{
}