#include "libCommon/Exception.hpp"
#include "libCommon/data/String.hpp"

namespace
{
std::string MakeMsg(const std::string &key)
{
    return util::Format("Key \"%s\" could not be found!", key.c_str());
}

std::string MakeMsg(const std::string &key, const std::string &msg)
{
    return util::Format("Key \"%s\" could not be found: \"%s\"", key.c_str(), msg.c_str());
}
} // namespace

util::MissingKeyException::MissingKeyException() : util::Exception()
{
}

util::MissingKeyException::MissingKeyException(const std::string &key) : util::Exception(MakeMsg(key))
{
}

util::MissingKeyException::MissingKeyException(const std::string &key, const std::string &msg) : util::Exception(MakeMsg(key, msg))
{
}