#include "Exception.hpp"

util::Exception::Exception() : msg("")
{
    std::printf("Created Exception!");
}

util::Exception::Exception(const std::string &msg) : errorCode(0),
                                                     msg(msg),
                                                     trace()
{
    std::printf("Created Exception! %s", msg.c_str());
}

util::Exception::Exception(int errorCode) : errorCode(errorCode),
                                            msg(),
                                            trace()
{
    std::printf("Created Exception! %s", msg.c_str());
}

util::Exception::Exception(int errorCode, const std::string &msg) : errorCode(errorCode),
                                                                    msg(msg),
                                                                    trace()
{
    std::printf("Created Exception! %s", msg.c_str());
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