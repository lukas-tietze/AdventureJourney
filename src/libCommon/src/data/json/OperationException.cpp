#include "data/Json.hpp"

json::OperationException::OperationException() : util::Exception("Invalid Operation!")
{
}

json::OperationException::OperationException(const std::string &msg) : util::Exception(msg)
{
}