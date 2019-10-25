#include "libCommon/io/Channel.hpp"

util::io::StdErrStreamChannel::StdErrStreamChannel Instance = util::io::StdErrStreamChannel();

util::io::StdErrStreamChannel::StdErrStreamChannel()
{
}

std::ostream &util::io::StdErrStreamChannel::StreamHandle()
{
    return std::cerr;
}

const std::ostream &util::io::StdErrStreamChannel::StreamHandle() const
{
    return std::cerr;
}
