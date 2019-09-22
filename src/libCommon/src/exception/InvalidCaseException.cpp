#include "libCommon/Exception.hpp"
#include "libCommon/data/String.hpp"

util::InvalidCaseException::InvalidCaseException() : util::Exception("Switch hit invalid case!")
{
}

util::InvalidCaseException::InvalidCaseException(const std::string &which) : util::Exception(util::Format("Switch hit invalid case for value \"%\"!",
                                                                                                          which.c_str()))
{
}

util::InvalidCaseException::InvalidCaseException(const std::string &which, const std::string &customMsg) : util::Exception(util::Format("Switch hit invalid case for value \"%\"! Message: %",
                                                                                                                                        which.c_str(),
                                                                                                                                        customMsg.c_str()))
{
}