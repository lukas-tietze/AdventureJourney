#include "Exception.hpp"
#include "data/String.hpp"

namespace
{
std::string MakeMsg(const std::string &which)
{
    return util::Format("Switch hit invalid case for value \"%s\"!",
                        which.c_str());
}

std::string MakeMsg(const std::string &which, const std::string &customMsg)
{
    return util::Format("Switch hit invalid case for value \"%s\"! %s",
                        which.c_str(),
                        customMsg.c_str());
}
} // namespace

util::InvalidCaseException::InvalidCaseException() : util::Exception("Switch hit invalid case!")
{
}

util::InvalidCaseException::InvalidCaseException(const std::string &which) : util::Exception(MakeMsg(which))
{
}

util::InvalidCaseException::InvalidCaseException(const std::string &which, const std::string &customMsg) : util::Exception(MakeMsg(which, customMsg))
{
}