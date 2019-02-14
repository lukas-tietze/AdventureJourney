#include <sstream>

#include "Exception.hpp"

std::string util::FormatStacktrace(const boost::stacktrace::stacktrace &trace, uint indent, uint maxLen, bool showAdress)
{
    std::stringstream buf;
    std::string indentBuffer = std::string(indent, ' ');

    uint pos = 0;

    for (const auto &frame : trace)
    {
        if (pos < 0 || pos >= maxLen)
        {
            break;
        }

        pos++;
        buf << indentBuffer << pos << '#';
        if (showAdress)
            buf << '[' << frame.address() << ']';

        buf << ' ' << frame.name();

        if (frame.source_line() != 0)
            buf << " in "
                << frame.source_file() << ":" << frame.source_line();

        buf << std::endl;
    }
    
    return buf.str();
}