#pragma

#include <iostream>
#include <cstdio>
#include <memory>
#include <fstream>
#include <sstream>
#include <type_traits>
#include <vector>

#include "libCommon/Exception.hpp"
#include "libCommon/TemplateUtils.hpp"

namespace util
{
namespace io
{
class InvalidHandleRequestedException : public util::Exception
{
public:
    InvalidHandleRequestedException();
};

class IChannel
{
public:
    virtual ~IChannel();

    virtual void Write(const std::string &s) = 0;
    virtual std::ostream &StreamHandle() = 0;
    virtual const std::ostream &StreamHandle() const = 0;
    virtual std::FILE *FileHandle() = 0;
    virtual const std::FILE *FileHandle() const = 0;
    virtual bool IsChannelBased() const = 0;
    virtual bool IsFileBased() const = 0;
    virtual void Flush() = 0;
};

template <typename T>
std::ostream &operator<<(IChannel &c, const T &t)
{
    static std::stringstream sb;

    sb.clear();
    sb << t;

    c.Write(sb.str());
}

using Channel = std::shared_ptr<IChannel>;

class FileChannel : public IChannel
{
private:
    std::FILE *file;

public:
    FileChannel(std::FILE *file);
    FileChannel(const FileChannel &);
    FileChannel(FileChannel &&);
    virtual ~FileChannel();

    void Write(const std::string &s);
    std::ostream &StreamHandle();
    const std::ostream &StreamHandle() const;
    std::FILE *FileHandle();
    const std::FILE *FileHandle() const;
    bool IsChannelBased() const;
    bool IsFileBased() const;
    void Flush();
};

class FileStdOutChannel : public FileChannel
{
public:
    FileStdOutChannel();
};

class FileStdErrChannel : public FileChannel
{
public:
    FileStdErrChannel();
};

class StreamChannel : public IChannel
{
public:
    virtual ~StreamChannel();

    void Write(const std::string &s);
    std::FILE *FileHandle();
    const std::FILE *FileHandle() const;
    bool IsChannelBased() const;
    bool IsFileBased() const;
    void Flush();
};

class FileStreamChannel : public StreamChannel
{
private:
    std::fstream stream;

public:
    FileStreamChannel(const std::string &fileName);
    FileStreamChannel(const FileStreamChannel &) = delete;
    FileStreamChannel(FileStreamChannel &&);
    ~FileStreamChannel();

    std::ostream &StreamHandle();
    const std::ostream &StreamHandle() const;
};

class StdOutStreamChannel : public StreamChannel
{
public:
    std::ostream &StreamHandle();
    const std::ostream &StreamHandle() const;
};

class StdErrStreamChannel : public StreamChannel
{
public:
    std::ostream &StreamHandle();
    const std::ostream &StreamHandle() const;
};

class StringStreamChannel : public StreamChannel
{
private:
    std::stringstream stream;

public:
    StringStreamChannel();
    StringStreamChannel(const StringStreamChannel &);
    StringStreamChannel(StringStreamChannel &&);

    std::string Value();

    std::ostream &StreamHandle();
    const std::ostream &StreamHandle() const;
};

class ForkChannel : public IChannel
{
private:
    std::vector<Channel> channels;

public:
    ForkChannel();
    ForkChannel(const std::initializer_list<Channel> &values);
    ForkChannel(const ForkChannel &);

    template <typename... TChannels>
    ForkChannel(const TChannels &... channels)
    {
        this->channels.reserve(sizeof...(TChannels));

        util::vectorize(this->channels, channels);
    }

    void Write(const std::string &s);
    std::ostream &StreamHandle();
    const std::ostream &StreamHandle() const;
    std::FILE *FileHandle();
    const std::FILE *FileHandle() const;
    bool IsChannelBased() const;
    bool IsFileBased() const;
    void Flush();

    Channel &operator[](size_t index);
    const Channel &operator[](size_t index) const;

    void Remove(size_t index);

    std::vector<Channel>::iterator begin();
    std::vector<Channel>::const_iterator cbegin();
    std::vector<Channel>::reverse_iterator rbegin();
    std::vector<Channel>::const_reverse_iterator crbegin();
    std::vector<Channel>::iterator end();
    std::vector<Channel>::const_iterator cend();
    std::vector<Channel>::reverse_iterator rend();
    std::vector<Channel>::const_reverse_iterator crend();
};

class FormattedChannel : public IChannel
{
private:
    bool active;
    bool showTime;
    std::string TimeFormat;
    util::io::Channel channel;

public:
    FormattedChannel() = default;

    FormattedChannel(util::io::Channel channel);

    bool IsActive() const;
    void SetActive(bool active);
    void SetShowTime(bool showTime);
    bool IsTimeShown() const;
    util::io::Channel GetChannel() const;
    void SetChannel(util::io::Channel);

    void Write(const std::string &s);
    std::ostream &StreamHandle();
    const std::ostream &StreamHandle() const;
    std::FILE *FileHandle();
    const std::FILE *FileHandle() const;
    bool IsChannelBased() const;
    bool IsFileBased() const;
    void Flush();
};

namespace channel
{
Channel OpenFile(const std::string &path);
Channel OpenStdErrFile();
Channel OpenStdOutFile();
Channel OpenFileStream(const std::string &path);
Channel OpenStdErrStream();
Channel OpenStdOutStream();
Channel OpenStringStream();

template <typename T, typename T2>
Channel Open(const T &t)
{
    return std::make_shared<T>(t);
}

template <class T, std::enable_if_t<std::is_base_of_v<IChannel, T> && std::is_copy_constructible_v<T>, int> = 0>
Channel Open(const T &t)
{
    return Channel(reinterpret_cast<T *>(new T(t)));
}

template <class T>
Channel Open()
{
    return Open(T::Instance);
}
} // namespace channel
} // namespace io
} // namespace util