#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "String.hpp"

namespace util
{
std::string ReadFile(const std::string &file);
bool TryReadFile(const std::string &file, std::string &buf);
void WriteFile(const std::string &file, const std::string &data);
void WriteFile(const std::string &path, const std::vector<std::string> &data);
bool TryWriteFile(const std::string &file, const std::string &data);
bool TryWriteFile(const std::string &path, const std::vector<std::string> &data);

template <class T>
int Print(const T &arg)
{
    std::stringstream s;
    s << arg;

    return std::printf("%s", s.str().c_str());
}

template <class TFirst, class... TArgs>
int Print(const std::string &format, const TFirst &first, const TArgs &... args)
{
    return std::printf("%s", util::Format(format, first, args...).c_str());
}

template <class T>
int PrintLine(const T &arg)
{
    std::stringstream s;
    s << arg;

    return std::printf("%s\n", s.str().c_str());
}

template <class TFirst, class... TArgs>
int PrintLine(const std::string &format, const TFirst &first, const TArgs &... args)
{
    return std::printf("%s\n", util::Format(format, first, args...).c_str());
}

class Channel
{
  private:
    std::FILE *file;
    bool active;

  public:
    Channel();
    Channel(const Channel &copyFrom);
    Channel(std::FILE *);

    Channel &operator=(const Channel &copyFrom);

    bool IsActive() const;
    bool IsOpen() const;
    void Close();
    void SetActive(bool active);

    const std::FILE *GetTarget() const;
    std::FILE *GetTarget();
    void SetTarget(std::FILE *);

    int Write2(const char *format, ...);
    int Write2(const char *format, va_list args);
    int WriteLine2(const char *format, ...);
    int WriteLine2(const char *format, va_list args);
    int Write2(const std::string &format, ...);
    int Write2(const std::string &format, va_list args);
    int WriteLine2(const std::string &format, ...);
    int WriteLine2(const std::string &format, va_list args);

    template <class TFirst, class... TArgs>
    int Write(const std::string &format, const TFirst &first, const TArgs &... args)
    {
        return std::fprintf(this->file, "%s\n", util::Format(format, first, args...).c_str());
    }

    template <class TFirst, class... TArgs>
    int WriteLine(const std::string &format, const TFirst &first, const TArgs &... args)
    {
        auto res = std::fprintf(this->file, "%s\n", util::Format(format, first, args...).c_str());

        std::fflush(this->file);

        return res;
    }

    template <class T>
    int Write(const T &arg)
    {
        std::stringstream s;
        s << arg;

        return std::fprintf(this->file, "%s", s.str().c_str());
    }

    template <class T>
    int WriteLine(const T &arg)
    {
        std::stringstream s;
        s << arg;

        auto res = std::fprintf(this->file, "%s\n", s.str().c_str());

        std::fflush(this->file);

        return res;
    }
};

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

    int Write2(CommunicationLevel, const char *, ...);
    int WriteLine2(CommunicationLevel, const char *, ...);
    int Write2(CommunicationLevel, const std::string &, ...);
    int WriteLine2(CommunicationLevel, const std::string &, ...);
    int Write2(CommunicationLevel, const std::string &);
    int WriteLine2(CommunicationLevel, const std::string &);

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

    Communicator &Message2(const char *, ...);
    Communicator &Message2(const std::string &, ...);
    Communicator &Debug2(const char *format, ...);
    Communicator &Debug2(const std::string &, ...);
    Communicator &Error2(const char *format, ...);
    Communicator &Error2(const std::string &, ...);

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
extern Channel out;
extern Channel err;
extern Communicator com;
} // namespace util