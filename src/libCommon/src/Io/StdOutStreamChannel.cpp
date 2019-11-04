#include "libCommon/io/Channel.hpp"

std::ostream &util::io::StdOutStreamChannel::StreamHandle()
{
    return std::cout;
}

const std::ostream &util::io::StdOutStreamChannel::StreamHandle() const
{
    return std::cout;
}
