#include "libCommon/Exception.hpp"
#include "libCommon/data/String.hpp"

util::NotImplementedException::NotImplementedException() : util::Exception("The function is not implemented!")
{
}

util::NotImplementedException::NotImplementedException(const std::string &msg) : util::Exception(util::Format("The function is not implemented! => %", msg))
{
}