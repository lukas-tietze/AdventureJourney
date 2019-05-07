#include "GlUtils.hpp"
#include "data/Io.hpp"

namespace
{
const std::string GlErrorMessageNoError = "NoError: No error has been recorded.";
const std::string GlErrorMessageInvalidEnum = "InvalidEnum: An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
const std::string GlErrorMessageInvalidValue = "InvalidValue: A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
const std::string GlErrorMessageInvalidOperation = "InvalidOperation: The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
const std::string GlErrorMessageInvalidFramebufferOperation = "InvalidFramebufferOperation: The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
const std::string GlErrorMessageOutOfMemory = "OutOfMemory: There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
const std::string GlErrorMessageStackUnderflow = "StackUnderflow: An attempt has been made to perform an operation that would cause an internal stack to underflow.";
const std::string GlErrorMessageStackOverflow = "StackOverflow: An attempt has been made to perform an operation that would cause an internal stack to overflow.";
const std::string GlErrorMessageUnknownError = "Unknown Error: GetGlErrorMessage() was called with in unkown error code!";
} // namespace

const std::string &glutil::GetGlErrorMessage(GLenum error)
{
    switch (error)
    {
    case GL_NO_ERROR:
        return GlErrorMessageNoError;
    case GL_INVALID_ENUM:
        return GlErrorMessageInvalidEnum;
    case GL_INVALID_VALUE:
        return GlErrorMessageInvalidValue;
    case GL_INVALID_OPERATION:
        return GlErrorMessageInvalidOperation;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return GlErrorMessageInvalidFramebufferOperation;
    case GL_OUT_OF_MEMORY:
        return GlErrorMessageOutOfMemory;
    case GL_STACK_UNDERFLOW:
        return GlErrorMessageStackUnderflow;
    case GL_STACK_OVERFLOW:
        return GlErrorMessageStackOverflow;
    default:
        return GlErrorMessageUnknownError;
    }
}

void glutil::ThrowOnGlError()
{
    auto error = glGetError();

    if (error != GL_NO_ERROR)
        throw GlErrorException(error);
}

void glutil::PrintGlError(const std::string &marker)
{
    auto error = glGetError();

    if (error != GL_NO_ERROR)
        util::out.WriteLine("%%", marker, glutil::GetGlErrorMessage(error));
}

void glutil::PrintAllGlErrors(const std::string &marker)
{
    auto error = glGetError();

    while (error != GL_NO_ERROR)
    {
        util::out.WriteLine("%%", marker, glutil::GetGlErrorMessage(error));
        error = glGetError();
    }
}