#include "libCommon/Exception.hpp"

util::Exception::Exception() : msg("")
{
}

util::Exception::Exception(const std::string &msg) : errorCode(0),
                                                     msg(msg),
                                                     trace()
{
}

util::Exception::Exception(int errorCode) : errorCode(errorCode),
                                            msg(),
                                            trace()
{
}

util::Exception::Exception(int errorCode, const std::string &msg) : errorCode(errorCode),
                                                                    msg(msg),
                                                                    trace()
{
}

const char *util::Exception::what() const throw()
{
    return this->msg.c_str();
}

const std::string &util::Exception::GetMessage() const
{
    return this->msg;
}

int util::Exception::GetErrorCode() const
{
    return this->errorCode;
}

const boost::stacktrace::stacktrace &util::Exception::GetStacktrace() const
{
    return this->trace;
}