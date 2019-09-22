#include <cstdarg>

#include "libCommon/data/Io.hpp"
#include "libCommon/Exception.hpp"

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

	return *this;
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