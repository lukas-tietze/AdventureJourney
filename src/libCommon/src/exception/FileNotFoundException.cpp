#include "libCommon/Exception.hpp
#include "libCommon/data/String.hpp"

util::FileNotFoundException::FileNotFoundException() : util::Exception()
{
}

util::FileNotFoundException::FileNotFoundException(const std::string &path) : util::Exception(util::Format("File \"%\" could not be found!", path))
{
}