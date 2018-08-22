#include "exception.hpp"
#include "data/string_conversions.hpp"

std::string make_msg(const std::string &key)
{
    return util::format("Key \"%s\" could not be found!", key.c_str());
}

std::string make_msg(const std::string &key, const std::string &msg)
{
    return util::format("Key \"%s\" could not be found: \"%s\"", key.c_str(), msg.c_str());
}

util::missing_key_exception::missing_key_exception() : util::exception()
{
}

util::missing_key_exception::missing_key_exception(const std::string &key) : util::exception(make_msg(key))
{
}

util::missing_key_exception::missing_key_exception(const std::string &key, const std::string &msg) : util::exception(make_msg(key, msg))
{
}