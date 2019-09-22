#include "libCommon/data/Json.hpp"

json::ParserException::ParserException() : util::Exception("Illegal token encountered")
{
}

json::ParserException::ParserException(const std::string &msg) : util::Exception(msg)
{
}