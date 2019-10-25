#include <cstdarg>

#include "libCommon/io/Writer.hpp"
#include "libCommon/io/Channel.hpp"
#include "libCommon/Exception.hpp"

util::io::Writer util::io::out = util::io::Writer(util::io::channel::OpenStdOutStream());
util::io::Writer util::io::err = util::io::Writer(util::io::channel::OpenStdErrStream());

const std::string util::io::Writer::TimeFormat = "%Y-%m-%d %H:%M:%S";

util::io::Writer::Writer() : active(true),
                             showTime(false)
{
}

util::io::Writer::Writer(const Writer &copyFrom) : active(copyFrom.active),
                                                   showTime(false)
{
}

util::io::Writer::Writer(std::FILE *target) : active(true),
                                              showTime(false)
{
}

void util::io::Writer::SetShowTime(bool show)
{
    this->showTime = show;
}

util::io::Writer &util::io::Writer::operator=(const Writer &copyFrom)
{
    if (this == &copyFrom)
        return *this;

    this->file = copyFrom.file;
    this->active = copyFrom.active;

    return *this;
}

bool util::io::Writer::IsActive() const
{
    return this->active;
}

bool util::io::Writer::IsOpen() const
{
    return this->file != nullptr;
}

void util::io::Writer::Close()
{
    this->file = nullptr;
}

void util::io::Writer::SetActive(bool active)
{
    this->active = active;
}

const std::FILE *util::io::Writer::GetTarget() const
{
    return this->file;
}

std::FILE *util::io::Writer::GetTarget()
{
    return this->file;
}

void util::io::Writer::SetTarget(std::FILE *target)
{
    this->file = target;
}

void util::io::Writer::WriteLine()
{
    std::fprintf(this->file, "\n");
}