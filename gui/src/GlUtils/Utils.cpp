#include "GlUtils.hpp"

GLenum HandleGlError()
{
    auto err = glGetError();

    //TODO: Fehler behandeln

    return err;
}