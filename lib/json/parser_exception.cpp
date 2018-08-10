#include "json.hpp"

json::parser::parser_exception::parser_exception() : std::runtime_error("Illegal token encountered")
{
}

json::parser::parser_exception::parser_exception(const std::string &msg) : std::runtime_error(msg)
{
}