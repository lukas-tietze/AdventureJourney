#include "libCommon/io/Channel.hpp"

util::io::StringStreamChannel::StringStreamChannel() : stream()
{
}

util::io::StringStreamChannel::StringStreamChannel(const StringStreamChannel &copy) : stream(copy.stream.str())
{
}

util::io::StringStreamChannel::StringStreamChannel(StringStreamChannel &&transfer) : stream(std::move(transfer.stream))
{
}

std::string util::io::StringStreamChannel::Value()
{
    return this->stream.str();
}

std::ostream &util::io::StringStreamChannel::StreamHandle()
{
    return this->stream;
}

const std::ostream &util::io::StringStreamChannel::StreamHandle() const
{
    return this->stream;
}
