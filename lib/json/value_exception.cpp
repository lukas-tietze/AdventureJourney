#include "json.hpp"

json::value_exception::value_exception() : std::runtime_error("Invalid value!")
{
}

json::value_exception::value_exception(const std::string &msg) : std::runtime_error(msg)
{
}