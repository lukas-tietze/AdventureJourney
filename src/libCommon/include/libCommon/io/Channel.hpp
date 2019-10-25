#pragma

#include <iostream>
#include <cstdio>
#include <memory>
#include <fstream>
#include <sstream>
#include <type_traits>
#include "libCommon/Exception.hpp"

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
private:
	FileStdOutChannel();

public:
	static FileStdOutChannel Instance;
};

class FileStdErrChannel : public FileChannel
{
private:
	FileStdErrChannel();

public:
	static FileStdErrChannel Instance;
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

class FileStreamChannel : public IChannel
{
private:
    std::fstream stream;

public:
    FileStreamChannel(const std::string &fileName);
    FileStreamChannel(const FileStreamChannel &) = delete
    FileStreamChannel(FileStreamChannel &&);
    ~FileStreamChannel();

    std::ostream &StreamHandle();
    const std::ostream &StreamHandle() const;
};

class StdOutStreamChannel : public IChannel
{
private:
    StdOutStreamChannel();

public:
    static StdOutStreamChannel Instance;

    std::ostream &StreamHandle();
    const std::ostream &StreamHandle() const;
};

class StdErrStreamChannel : public IChannel
{
private:
    StdErrStreamChannel();

public:
    static StdErrStreamChannel Instance;

    std::ostream &StreamHandle();
    const std::ostream &StreamHandle() const;
};

class StringStreamChannel : public IChannel
{
private:
    std::stringstream stream;

public:
    StringStreamChannel();
    StringStreamChannel(const StringStreamChannel &);
    StringStreamChannel(StringStreamChannel &&);

    const std::string &Value();

    std::ostream &StreamHandle();
    const std::ostream &StreamHandle() const;
};

using Channel = std::shared_ptr<IChannel>;

namespace channel
{
Channel OpenFile(const std::string &path);
Channel OpenStdErrFile();
Channel OpenStdOutFile();
Channel OpenFileStream(const std::string &path);
Channel OpenStdErrStream();
Channel OpenStdOutStream();
Channel OpenStringStream();

template<typename T, typename T2>
Channel Open(const T& t) {

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