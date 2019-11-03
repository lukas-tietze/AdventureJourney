#include "libCommon/io/Channel.hpp"

util::io::ForkChannel::ForkChannel() : channels()
{
}

util::io::ForkChannel::ForkChannel(const std::initializer_list<Channel> &values) : channels(values)
{
}

util::io::ForkChannel::ForkChannel(const ForkChannel &other) : channels(other.channels)
{
}

void util::io::ForkChannel::Write(const std::string &s)
{
    for (auto channel : this->channels)
    {
        channel->Write(s);
    }
}

std::ostream &util::io::ForkChannel::StreamHandle()
{
    throw InvalidHandleRequestedException();
}

const std::ostream &util::io::ForkChannel::StreamHandle() const
{
    throw InvalidHandleRequestedException();
}

std::FILE *util::io::ForkChannel::FileHandle()
{
    throw InvalidHandleRequestedException();
}

const std::FILE *util::io::ForkChannel::FileHandle() const
{
    throw InvalidHandleRequestedException();
}

bool util::io::ForkChannel::IsChannelBased() const
{
    return false;
}

bool util::io::ForkChannel::IsFileBased() const
{
    return false;
}

void util::io::ForkChannel::Flush()
{
    for (auto channel : this->channels)
    {
        channel->Flush();
    }
}

util::io::Channel &util::io::ForkChannel::operator[](size_t index)
{
    return this->channels[index];
}

const util::io::Channel &util::io::ForkChannel::operator[](size_t index) const
{
    return this->channels[index];
}

void util::io::ForkChannel::Remove(size_t index)
{
    this->channels.erase(this->channels.begin() + index);
}

std::vector<util::io::Channel>::iterator util::io::ForkChannel::begin()
{
    return this->channels.begin();
}

std::vector<util::io::Channel>::const_iterator util::io::ForkChannel::cbegin()
{
    return this->channels.cbegin();
}

std::vector<util::io::Channel>::reverse_iterator util::io::ForkChannel::rbegin()
{
    return this->channels.rbegin();
}

std::vector<util::io::Channel>::const_reverse_iterator util::io::ForkChannel::crbegin()
{
    return this->channels.crbegin();
}

std::vector<util::io::Channel>::iterator util::io::ForkChannel::end()
{
    return this->channels.end();
}

std::vector<util::io::Channel>::const_iterator util::io::ForkChannel::cend()
{
    return this->channels.cend();
}

std::vector<util::io::Channel>::reverse_iterator util::io::ForkChannel::rend()
{
    return this->channels.rend();
}

std::vector<util::io::Channel>::const_reverse_iterator util::io::ForkChannel::crend()
{
    return this->channels.crend();
}
