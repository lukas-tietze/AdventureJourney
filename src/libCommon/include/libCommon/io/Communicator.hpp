#pragma once

#include "Channel.hpp"

namespace util
{
namespace io
{
enum class CommunicationLevel
{
    None = 0,
    Error = 1,
    Message = 2,
    Debug = 3,
};

class Communicator
{
private:
    Channel message;
    Channel debug;
    Channel error;
    Channel deadChannel;

    CommunicationLevel communicationLevel;

    Channel &SelectChannel(CommunicationLevel);

public:
    Communicator();
    Communicator(const Communicator &copyFrom);

    Communicator &operator=(const Communicator &);

    CommunicationLevel GetCommunicationLevel() const;
    void SetCommunicationLevel(CommunicationLevel level);

    Channel &GetMessageChanell();
    Channel &GetDebugChannel();
    Channel &GetErrorChannel();

    const Channel &GetMessageChanell() const;
    const Channel &GetDebugChannel() const;
    const Channel &GetErrorChannel() const;

    template <class TFirst, class... TArgs>
    int Write(CommunicationLevel importance, const std::string &format, const TFirst &first, const TArgs &... args)
    {
        return this->SelectChannel(importance).Write(format, first, args...);
    }

    template <class TFirst, class... TArgs>
    int WriteLine(CommunicationLevel importance, const std::string &format, const TFirst &first, const TArgs &... args)
    {
        return this->SelectChannel(importance).WriteLine(format, first, args...);
    }

    template <class T>
    int Write(CommunicationLevel importance, const T &arg)
    {
        return this->SelectChannel(importance).Write(arg);
    }

    template <class T>
    int WriteLine(CommunicationLevel importance, const T &arg)
    {
        return this->SelectChannel(importance).WriteLine(arg);
    }

    template <class TFirst, class... TArgs>
    Communicator &Message(const std::string &format, const TFirst &first, const TArgs &... args)
    {
        this->SelectChannel(CommunicationLevel::Message).WriteLine(format, first, args...);

        return *this;
    }

    template <class TFirst, class... TArgs>
    Communicator &Debug(const std::string &format, const TFirst &first, const TArgs &... args)
    {
        this->SelectChannel(CommunicationLevel::Debug).WriteLine(format, first, args...);

        return *this;
    }

    template <class TFirst, class... TArgs>
    Communicator &Error(const std::string &format, const TFirst &first, const TArgs &... args)
    {
        this->SelectChannel(CommunicationLevel::Error).WriteLine(format, first, args...);

        return *this;
    }
};

extern Communicator stdcom;
} // namespace io
} // namespace  util