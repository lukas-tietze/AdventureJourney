#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace util
{
std::string ReadFile(const std::string &file);

bool TryReadFile(const std::string &file, std::string &buf);

void WriteFile(const std::string &file, const std::string &data);

void WriteFile(const std::string &path, const std::vector<std::string &> data);

bool TryWriteFile(const std::string &file, const std::string &data);

bool TryWriteFile(const std::string &path, const std::vector<std::string &> data);

template <class T>
int PrintR(const T &obj)
{
    std::stringstream stream;

    stream << obj;

    return std::printf("%s", stream.str().c_str());
}

template <class T>
int PrintP(const T *obj)
{
    std::stringstream stream;

    obj->operator<<(stream);

    stream << std::endl;

    return std::printf("%s", stream.str().c_str());
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

    int Print(const char *format, ...);
    int Print(const char *format, va_list args);
    int PrintLine(const char *format, ...);
    int PrintLine(const char *format, va_list args);
    int Print(const std::string &format, ...);
    int Print(const std::string &format, va_list args);
    int PrintLine(const std::string &format, ...);
    int PrintLine(const std::string &format, va_list args);
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

    int Print(CommunicationLevel importance, const char *format, ...);
    int PrintLine(CommunicationLevel importance, const char *format, ...);
    int Print(CommunicationLevel importance, const std::string &format, ...);
    int PrintLine(CommunicationLevel importance, const std::string &format, ...);

    Communicator &Message(const char *format, ...);
    Communicator &Message(const std::string &format, ...);
    Communicator &Debug(const char *format, ...);
    Communicator &Debug(const std::string &format, ...);
    Communicator &Error(const char *format, ...);
    Communicator &Error(const std::string &format, ...);
};
} // namespace util