#include "libCommon/Exception.hpp"
#include "libCommon/data/String.hpp"

util::NotSupportedException::NotSupportedException() : util::Exception("The process is not supported!")
{
}

util::NotSupportedException::NotSupportedException(const std::string &msg) : util::Exception(util::Format("The process is not supported! => %", msg))
{
}