#include "libCommon/io/Channel.hpp"

std::ostream &util::io::StdErrStreamChannel::StreamHandle()
{
    return std::cerr;
}

const std::ostream &util::io::StdErrStreamChannel::StreamHandle() const
{
    return std::cerr;
}
