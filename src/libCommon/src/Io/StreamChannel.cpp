#include "libCommon/io/Channel.hpp"

util::io::StreamChannel::~StreamChannel()
{
    this->StreamHandle().flush();
}

void util::io::StreamChannel::Write(const std::string &s)
{
    this->StreamHandle() << s;
}

std::FILE *util::io::StreamChannel::FileHandle()
{
    throw InvalidHandleRequestedException();
}

const std::FILE *util::io::StreamChannel::FileHandle() const
{
    throw InvalidHandleRequestedException();
}

bool util::io::StreamChannel::IsChannelBased() const
{
    return true;
}

bool util::io::StreamChannel::IsFileBased() const
{
    return false;
}

void util::io::StreamChannel::Flush()
{
    this->StreamHandle().flush();
}
