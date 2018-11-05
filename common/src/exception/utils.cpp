#include <sstream>

#include "exception.hpp"

std::string print_stacktrace(const boost::stacktrace::stacktrace &trace, uint indent, uint maxLen)
{
    std::stringstream buf;
    std::string indentBuffer = std::string(' ', indent);

    uint pos = 0;

    for (const auto &frame : trace)
    {
        if (pos >= maxLen)
        {
            break;
        }

        pos++;
        buf << indentBuffer;
        buf << frame.name() << std::endl;
    }

    return buf.str();
}