#include "exception.hpp"
#include "data/string.hpp"

std::string make_msg(const std::string &which)
{
    return util::format("Switch hit invalid case for value \"%s\"!",
                        which.c_str());
}

std::string make_msg(const std::string &which, const std::string &customMsg)
{
    return util::format("Switch hit invalid case for value \"%s\"! %s",
                        which.c_str(),
                        customMsg.c_str());
}

util::invalid_case_exception::invalid_case_exception() : util::exception("Switch hit invalid case!")
{
}

util::invalid_case_exception::invalid_case_exception(const std::string &which) : util::exception(make_msg(which))
{
}

util::invalid_case_exception::invalid_case_exception(const std::string &which, const std::string &customMsg) : util::exception(make_msg(which, customMsg))
{
}