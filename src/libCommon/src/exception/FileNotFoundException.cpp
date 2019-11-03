#include "libCommon/data/String.hpp"
#include "libCommon/Exception.hpp"

util::FileNotFoundException::FileNotFoundException() : util::Exception()
{
}

util::FileNotFoundException::FileNotFoundException(const std::string &path) : util::Exception(util::Format("File \"%\" could not be found!", path))
{
}