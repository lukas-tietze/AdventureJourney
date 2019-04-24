#include "GlUtils.hpp"
#include "data/Io.hpp"

void glutil::PrintGlError(GLenum error)
{
    switch (error)
    {
    case GL_NO_ERROR:
        util::dbg.WriteLine("GlError: No error has been recorded. The value of this symbolic constant is guaranteed to be 0.");
        break;

    case GL_INVALID_ENUM:
        util::dbg.WriteLine("GlError: An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.");
        break;

    case GL_INVALID_VALUE:
        util::dbg.WriteLine("GlError: A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.");
        break;

    case GL_INVALID_OPERATION:
        util::dbg.WriteLine("GlError: The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.");
        break;

    case GL_INVALID_FRAMEBUFFER_OPERATION:
        util::dbg.WriteLine("GlError: The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.");
        break;

    case GL_OUT_OF_MEMORY:
        util::dbg.WriteLine("GlError: There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.");
        break;

    case GL_STACK_UNDERFLOW:
        util::dbg.WriteLine("GlError: An attempt has been made to perform an operation that would cause an internal stack to underflow.");
        break;

    case GL_STACK_OVERFLOW:
        util::dbg.WriteLine("GlError: An attempt has been made to perform an operation that would cause an internal stack to overflow.");
        break;
    }
}

int glutil::HandleGlErrors()
{
    int errCount = 0;
    GLenum error = glGetError();

    while (error != GL_NO_ERROR)
    {
        PrintGlError(error);
        error = glGetError();
        errCount++;
    }

    return errCount;
}