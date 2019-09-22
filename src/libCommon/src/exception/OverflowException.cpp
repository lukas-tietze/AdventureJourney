#include "libCommon/Exception.hpp"
#include "libCommon/data/String.hpp"

namespace
{
std::string MakeMsg(int max)
{
    return util::Format("Collection overflow! Can't contain more than %i elements!", max);
}

std::string MakeMsg(int max, const std::string &msg)
{
    return util::Format("Collection overflow! Can't contain more than %i elements: \"%s\"", max, msg.c_str());
}
} // namespace

util::OverflowException::OverflowException() : util::Exception("Collection overflow!")
{
}

util::OverflowException::OverflowException(int max) : util::Exception(MakeMsg(max))
{
}

util::OverflowException::OverflowException(int max, const std::string &msg) : util::Exception(MakeMsg(max, msg))
{
}