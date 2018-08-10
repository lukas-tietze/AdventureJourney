#include "json.hpp"

json::operation_exception::operation_exception() : std::runtime_error("Invalid Operation!")
{
}

json::operation_exception::operation_exception(const std::string &msg) : std::runtime_error(msg)
{
}