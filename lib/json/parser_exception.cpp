#include "json.hpp"

json::parser::parser_exception::parser_exception() : util::exception("Illegal token encountered")
{
}

json::parser::parser_exception::parser_exception(const std::string &msg) : util::exception(msg)
{
}