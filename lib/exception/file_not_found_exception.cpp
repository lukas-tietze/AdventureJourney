#include "exception.hpp"

util::file_not_found_exception::file_not_found_exception() : util::exception()
{
}

util::file_not_found_exception::file_not_found_exception(const std::string &path) : util::exception("File \"" + path + "\" could not be found!")
{
}