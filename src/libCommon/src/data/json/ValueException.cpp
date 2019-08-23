#include "data/Json.hpp"

json::ValueException::ValueException() : util::Exception("Invalid value!")
{
}

json::ValueException::ValueException(const std::string &msg) : util::Exception(msg)
{
}