#include "libCommon/Exception.hpp"
#include "libCommon/data/String.hpp"

namespace
{
std::string MakeMsg(int index, int max)
{
    return util::Format("Index was out of range %i (max %i)", index, max);
}

std::string MakeMsg(int index, int max, const std::string &msg)
{
    return util::Format("Index was out of range %i (max %i): \"%s\"", index, max, msg.c_str());
}
} // namespace

util::IndexOutOfRangeException::IndexOutOfRangeException() : util::Exception("Index was out of range!")
{
}

util::IndexOutOfRangeException::IndexOutOfRangeException(int index, int max) : util::Exception(MakeMsg(index, max))
{
}

util::IndexOutOfRangeException::IndexOutOfRangeException(int index, int max, const std::string &msg) : util::Exception(MakeMsg(index, max, msg))
{
}