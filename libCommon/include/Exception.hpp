#pragma once

#include "Defs.hpp"

#include <stdexcept>
#include <string>
#include <sstream>

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

protected:
    void SetMessage(const std::string &message);

public:
    Exception();
    Exception(int);
    Exception(const std::string &);
    Exception(int, const std::string &);

    const char *what() const throw();
    const std::string &GetMessage() const;
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

class NotSupportedException : public util::Exception
{
public:
    NotSupportedException();
    NotSupportedException(const std::string &customMsg);
};

class NotImplementedException : public util::Exception
{
public:
    NotImplementedException();
    NotImplementedException(const std::string &customMsg);
};

class InvalidCaseException : public util::Exception
{
public:
    InvalidCaseException();
    InvalidCaseException(const std::string &which);
    InvalidCaseException(const std::string &which, const std::string &customMsg);

    template <class TEnum>
    static InvalidCaseException MakeException(TEnum value)
    {
        std::stringstream s[2];

        s[0] << static_cast<int>(value);
        s[1] << '"' << static_cast<int>(value) << "\" is no valid enum value for type \"" << typeid(TEnum).name() << '"';

        return InvalidCaseException(s[0].str(), s[1].str());
    }
};
} // namespace util