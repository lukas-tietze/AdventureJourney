#include <cstdarg>

#include "data/Io.hpp"
#include "Exception.hpp"

util::Communicator::Communicator() : message(stdout),
                                     debug(stderr),
                                     error(stderr),
                                     deadChannel(nullptr)
{
}

util::Communicator::Communicator(const Communicator &copyFrom) : message(copyFrom.message),
                                                                 debug(copyFrom.debug),
                                                                 error(copyFrom.error),
                                                                 deadChannel(nullptr),
                                                                 communicationLevel(copyFrom.communicationLevel)
{
}

util::Communicator &util::Communicator::operator=(const Communicator &copyFrom)
{
    this->message = copyFrom.message;
    this->debug = copyFrom.debug;
    this->error = copyFrom.error;
    this->communicationLevel = copyFrom.communicationLevel;
}

util::CommunicationLevel util::Communicator::GetCommunicationLevel() const
{
    return this->communicationLevel;
}

void util::Communicator::SetCommunicationLevel(CommunicationLevel level)
{
    this->communicationLevel = level;

    this->debug.SetActive(this->communicationLevel >= CommunicationLevel::Debug);
    this->error.SetActive(this->communicationLevel >= CommunicationLevel::Error);
    this->message.SetActive(this->communicationLevel >= CommunicationLevel::Message);
}

util::Channel &util::Communicator::GetMessageChanell()
{
    return this->message;
}

util::Channel &util::Communicator::GetDebugChannel()
{
    return this->debug;
}

util::Channel &util::Communicator::GetErrorChannel()
{
    return this->error;
}

const util::Channel &util::Communicator::GetMessageChanell() const
{
    return this->message;
}

const util::Channel &util::Communicator::GetDebugChannel() const
{
    return this->debug;
}

const util::Channel &util::Communicator::GetErrorChannel() const
{
    return this->error;
}

int util::Communicator::Write2(CommunicationLevel importance, const char *format, ...)
{
    if (importance <= this->communicationLevel)
    {
        va_list args;
        va_start(args, format);
        this->SelectChannel(importance).Write2(format, args);
        va_end(args);
    }
}

int util::Communicator::WriteLine2(CommunicationLevel importance, const char *format, ...)
{
    if (importance <= this->communicationLevel)
    {
        va_list args;
        va_start(args, format);
        this->SelectChannel(importance).WriteLine2(format, args);
        va_end(args);
    }
}

int util::Communicator::Write2(CommunicationLevel importance, const std::string &format, ...)
{
    if (importance <= this->communicationLevel)
    {
        va_list args;
        va_start(args, format);
        this->SelectChannel(importance).Write2(format, args);
        va_end(args);
    }
}

int util::Communicator::WriteLine2(CommunicationLevel importance, const std::string &format, ...)
{
    if (importance <= this->communicationLevel)
    {
        va_list args;
        va_start(args, format);
        this->SelectChannel(importance).WriteLine2(format, args);
        va_end(args);
    }
}

util::Communicator &util::Communicator::Message2(const char *format, ...)
{
    if (CommunicationLevel::Message <= this->communicationLevel)
    {
        va_list args;
        va_start(args, format);
        this->SelectChannel(CommunicationLevel::Message).Write2(format, args);
        va_end(args);
    }
}

util::Communicator &util::Communicator::Message2(const std::string &format, ...)
{
    if (CommunicationLevel::Message <= this->communicationLevel)
    {
        va_list args;
        va_start(args, format);
        this->SelectChannel(CommunicationLevel::Message).Write2(format, args);
        va_end(args);
    }
}

util::Communicator &util::Communicator::Debug2(const char *format, ...)
{
    if (CommunicationLevel::Debug <= this->communicationLevel)
    {
        va_list args;
        va_start(args, format);
        this->SelectChannel(CommunicationLevel::Debug).Write2(format, args);
        va_end(args);
    }
}

util::Communicator &util::Communicator::Debug2(const std::string &format, ...)
{
    if (CommunicationLevel::Debug <= this->communicationLevel)
    {
        va_list args;
        va_start(args, format);
        this->SelectChannel(CommunicationLevel::Debug).Write2(format, args);
        va_end(args);
    }
}

util::Communicator &util::Communicator::Error2(const char *format, ...)
{
    if (CommunicationLevel::Error <= this->communicationLevel)
    {
        va_list args;
        va_start(args, format);
        this->SelectChannel(CommunicationLevel::Error).Write2(format, args);
        va_end(args);
    }
}

util::Communicator &util::Communicator::Error2(const std::string &format, ...)
{
    if (CommunicationLevel::Error <= this->communicationLevel)
    {
        va_list args;
        va_start(args, format);
        this->SelectChannel(CommunicationLevel::Error).Write2(format, args);
        va_end(args);
    }
}

util::Channel &util::Communicator::SelectChannel(CommunicationLevel level)
{
    switch (level)
    {
    case CommunicationLevel::None:
        return this->deadChannel;
        break;
    case CommunicationLevel::Error:
        return this->error;
        break;
    case CommunicationLevel::Message:
        return this->message;
        break;
    case CommunicationLevel::Debug:
        return this->debug;
        break;
    default:
        throw util::InvalidCaseException();
    }
}