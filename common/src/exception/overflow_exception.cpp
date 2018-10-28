#include "exception.hpp"
#include "data/string.hpp"

std::string make_text(int max)
{
    return util::format("Collection overflow! Can't contain more than %i elements!", max);
}

std::string make_text(int max, const std::string &msg)
{
    return util::format("Collection overflow! Can't contain more than %i elements: \"%s\"", max, msg.c_str());
}

util::overflow_exception::overflow_exception() : util::exception("Collection overflow!")
{
}

util::overflow_exception::overflow_exception(int max) : util::exception(make_text(max))
{
}

util::overflow_exception::overflow_exception(int max, const std::string &msg) : util::exception(make_text(max, msg))
{
}