#include "libCommon/io/Channel.hpp"

util::io::StdOutStreamChannel::StdOutStreamChannel util::io::StdOutStreamChannel::Instance = util::io::StdOutStreamChannel();

util::io::StdOutStreamChannel::StdOutStreamChannel()
{
}

std::ostream &util::io::StdOutStreamChannel::StreamHandle()
{
    return std::cout;
}

const std::ostream &util::io::StdOutStreamChannel::StreamHandle() const
{
    return std::cout;
}
