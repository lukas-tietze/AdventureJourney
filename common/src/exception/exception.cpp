#include "exception.hpp"

util::exception::exception() : msg("")
{
}

util::exception::exception(const std::string &msg) : error_code(0),
                                                     msg(msg)
{
}

util::exception::exception(int errorCode) : error_code(errorCode),
                                            msg()
{
}

util::exception::exception(int errorCode, const std::string &msg) : error_code(errorCode),
                                                                    msg(msg)
{
}

const char *util::exception::what() const throw()
{
    return this->msg.c_str();
}

const std::string &util::exception::get_message() const
{
    return this->msg;
}

int util::exception::get_error_code() const
{
    return this->error_code;
}