#include "data/json.hpp"

json::operation_exception::operation_exception() : util::exception("Invalid Operation!")
{
}

json::operation_exception::operation_exception(const std::string &msg) : util::exception(msg)
{
}