#include "exception.hpp"
#include "data/string_conversions.hpp"

std::string make_text(int index, int max)
{
    return util::format("Index out of range %i (max %i)", index, max);
}

std::string make_text(int index, int max, const std::string &msg)
{
    return util::format("Index out of range %i (max %i): \"%s\"", index, max, msg.c_str());
}

util::index_out_of_range_exception::index_out_of_range_exception() : util::exception()
{
}

util::index_out_of_range_exception::index_out_of_range_exception(int index, int max) : util::exception(make_text(index, max))
{
}

util::index_out_of_range_exception::index_out_of_range_exception(int index, int max, const std::string &msg) : util::exception(make_text(index, max, msg))
{
}