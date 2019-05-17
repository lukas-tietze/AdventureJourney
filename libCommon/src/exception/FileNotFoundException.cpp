#include "Exception.hpp"
#include "data/Io.hpp"

util::FileNotFoundException::FileNotFoundException() : util::Exception()
{
}

util::FileNotFoundException::FileNotFoundException(const std::string &path) : util::Exception(util::Format("File \"%\" could not be found!", path))
{
}