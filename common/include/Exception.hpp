#pragma once

#include <stdexcept>
#include <string>

#include <boost/stacktrace/stacktrace.hpp>

namespace util
{
namespace error_codes
{
const std::string &GetMessage(int errorCode);
}

std::string FormatStacktrace(const boost::stacktrace::stacktrace &trace, uint indent, uint maxLen, bool showAddress = false);

class Exception : public std::exception
{
  private:
    int errorCode;
    std::string msg;
    boost::stacktrace::stacktrace trace;

  public:
    Exception();
    Exception(int);
    Exception(const std::string &);
    Exception(int, const std::string &);

    virtual const char *what() const throw();
    virtual const std::string &GetMessage() const;
    int GetErrorCode() const;
    const boost::stacktrace::stacktrace &GetStacktrace() const;
};

class IndexOutOfRangeException : public util::Exception
{
  public:
    IndexOutOfRangeException();
    IndexOutOfRangeException(int index, int max);
    IndexOutOfRangeException(int index, int max, const std::string &customMsg);
};

class OverflowException : public util::Exception
{
  public:
    OverflowException();
    OverflowException(int max);
    OverflowException(int max, const std::string &customMsg);
};

class MissingKeyException : public util::Exception
{
  public:
    MissingKeyException();
    MissingKeyException(const std::string &key);
    MissingKeyException(const std::string &key, const std::string &customMsg);
};

class FileNotFoundException : public util::Exception
{
  public:
    FileNotFoundException();
    FileNotFoundException(const std::string &path);
    FileNotFoundException(const std::string &path, const std::string &customMsg);
};

class InvalidCaseException : public util::Exception
{
  public:
    InvalidCaseException();
    InvalidCaseException(const std::string &which);
    InvalidCaseException(const std::string &which, const std::string &customMsg);
};
} // namespace util