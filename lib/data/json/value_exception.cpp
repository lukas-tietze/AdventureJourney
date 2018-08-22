#include "data/json.hpp"

json::value_exception::value_exception() : util::exception("Invalid value!")
{
}

json::value_exception::value_exception(const std::string &msg) : util::exception(msg)
{
}