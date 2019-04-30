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
} // namespace

const std::string &glutil::GetGlErrorMessage(GLenum error)
{
    switch (error)
    {
    case GL_NO_ERROR:
        return GlErrorMessageNoError;
        break;

    case GL_INVALID_ENUM:
        return GlErrorMessageInvalidEnum;
        break;

    case GL_INVALID_VALUE:
        return GlErrorMessageInvalidValue;
        break;

    case GL_INVALID_OPERATION:
        return GlErrorMessageInvalidOperation;
        break;

    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return GlErrorMessageInvalidFramebufferOperation;
        break;

    case GL_OUT_OF_MEMORY:
        return GlErrorMessageOutOfMemory;
        break;

    case GL_STACK_UNDERFLOW:
        return GlErrorMessageStackUnderflow;
        break;

    case GL_STACK_OVERFLOW:
        return GlErrorMessageStackOverflow;
        break;
    }
}

void glutil::ThrowOnGlError()
{
    auto error = glGetError();

    if (error != GL_NO_ERROR)
        throw GlErrorException(error);
}