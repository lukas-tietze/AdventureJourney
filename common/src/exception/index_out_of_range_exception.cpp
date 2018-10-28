#include "exception.hpp"
#include "data/string.hpp"

std::string make_text(int index, int max)
{
    return util::format("Index was out of range %i (max %i)", index, max);
}

std::string make_text(int index, int max, const std::string &msg)
{
    return util::format("Index was out of range %i (max %i): \"%s\"", index, max, msg.c_str());
}

util::index_out_of_range_exception::index_out_of_range_exception() : util::exception("Index was out of range!")
{
}

util::index_out_of_range_exception::index_out_of_range_exception(int index, int max) : util::exception(make_text(index, max))
{
}

util::index_out_of_range_exception::index_out_of_range_exception(int index, int max, const std::string &msg) : util::exception(make_text(index, max, msg))
{
}