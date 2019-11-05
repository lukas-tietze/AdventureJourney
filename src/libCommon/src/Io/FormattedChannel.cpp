#include "libCommon/io/Channel.hpp"

util::io::FormattedChannel::FormattedChannel(util::io::Channel channel) : channel(channel)
{
}

bool util::io::FormattedChannel::IsActive() const
{
    return this->active;
}

void util::io::FormattedChannel::SetActive(bool active)
{
    this->active = active;
}

void util::io::FormattedChannel::SetShowTime(bool showTime)
{
    this->showTime = showTime;
}

util::io::Channel util::io::FormattedChannel::GetChannel() const
{
    return this->channel;
}

void util::io::FormattedChannel::SetChannel(util::io::Channel channel)
{
    this->channel = channel;
}

void util::io::FormattedChannel::Write(const std::string &s)
{
    if (this->channel && this->active)
    {
        if (this->showTime)
        {
            // TODO Zeitstempel schreiben
        }

        this->channel.Write(s);
    }
}

std::ostream &util::io::FormattedChannel::StreamHandle()
{
    return this->channel->StreamHandle();
}

const std::ostream &util::io::FormattedChannel::StreamHandle() const
{
    return this->channel->StreamHandle();
}

std::FILE *util::io::FormattedChannel::FileHandle()
{
    return this->channel->FileHandle();
}

const std::FILE *util::io::FormattedChannel::FileHandle() const
{
    return this->channel->FileHandle();
}

bool util::io::FormattedChannel::IsChannelBased() const
{
    return this->channel->IsChannelBased();
}

bool util::io::FormattedChannel::IsFileBased() const
{
    return this->channel->IsFileBase();
}

void util::io::FormattedChannel::Flush()
{
    this->channel->Flush();
}
