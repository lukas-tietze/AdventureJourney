#include "Exception.hpp"

util::FileNotFoundException::FileNotFoundException() : util::Exception()
{
}

util::FileNotFoundException::FileNotFoundException(const std::string &path) : util::Exception("File \"" + path + "\" could not be found!")
{
}