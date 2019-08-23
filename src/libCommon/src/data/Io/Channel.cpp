#include <cstdarg>

#include "data/Io.hpp"
#include "Exception.hpp"

const std::string util::Channel::TimeFormat = "%Y-%m-%d %H:%M:%S";

util::Channel::Channel() : file(stdout),
                           active(true),
                           showTime(false)
{
}

util::Channel::Channel(const Channel &copyFrom) : file(copyFrom.file),
                                                  active(copyFrom.active),
                                                  showTime(false)
{
}

util::Channel::Channel(std::FILE *target) : file(target),
                                            active(true),
                                            showTime(false)
{
}

void util::Channel::SetShowTime(bool show)
{
    this->showTime = show;
}

util::Channel &util::Channel::operator=(const Channel &copyFrom)
{
    if (this == &copyFrom)
        return *this;

    this->file = copyFrom.file;
    this->active = copyFrom.active;

    return *this;
}

bool util::Channel::IsActive() const
{
    return this->active;
}

bool util::Channel::IsOpen() const
{
    return this->file != nullptr;
}

void util::Channel::Close()
{
    this->file = nullptr;
}

void util::Channel::SetActive(bool active)
{
    this->active = active;
}

const std::FILE *util::Channel::GetTarget() const
{
    return this->file;
}

std::FILE *util::Channel::GetTarget()
{
    return this->file;
}

void util::Channel::SetTarget(std::FILE *target)
{
    this->file = target;
}

void util::Channel::WriteLine()
{
    std::fprintf(this->file, "\n");
}