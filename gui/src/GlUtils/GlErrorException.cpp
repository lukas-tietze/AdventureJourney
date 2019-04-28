#include "GlUtils.hpp"
#include "data/String.hpp"

glutil::GlErrorException::GlErrorException(GLenum error) : util::Exception(util::Format("GlError occurred: %", glutil::GetGlErrorMessage(error)))
{
}
