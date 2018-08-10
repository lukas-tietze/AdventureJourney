#include "data.hpp"

util::exception::exception() : msg("")
{
}

util::exception::exception(const std::string &msg) : msg(msg)
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