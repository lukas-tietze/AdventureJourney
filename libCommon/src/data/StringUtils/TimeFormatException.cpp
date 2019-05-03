#include "data/String.hpp"

util::TimeFormatException::TimeFormatException(const std::string &format, std::time_t time)
    : util::Exception(util::Format("Failed to format time!\nFormat=\"%\", Time=% (%)",
                                   format,
                                   time,
                                   std::string(std::ctime(&time))))
{
}