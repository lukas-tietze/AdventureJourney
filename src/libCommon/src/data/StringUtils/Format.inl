#include "libCommon/data/String.hpp"

namespace
{
struct ArrayAccess
{
    size_t start;
    size_t end;
    size_t step;
};

ArrayAccess ComputeArrayAccess(const std::string &format)
{
    ArrayAccess res;

    size_t endSep = format.find(':');
    size_t stepSep = format.find(':', endSep);

    if (endSep == std::string::npos)
        throw util::FormatException("Array specifier has seperator ':'!");

    if (endSep == 0)
        res.start = 0;
    else if (!util::ParseIntegral(format.substr(0, endSep - 1), res.start))
        throw util::FormatException("Illegal value for array start");

    if (stepSep == std::string::npos)
    {
        if (!util::ParseIntegral(format.substr(endSep + 1), res.end))
            throw util::FormatException("Illegal value for array end");
    }
    else
    {
        if (!util::ParseIntegral(format.substr(endSep + 1, stepSep - endSep - 1), res.end))
            throw util::FormatException("Illegal value for array end");

        if (!util::ParseIntegral(format.substr(stepSep + 1), res.step))
            throw util::FormatException("Illegal value for array step");
    }

    return res;
}

size_t PrepareFormat(const std::string &format, std::stringstream &buf, size_t pos)
{
    auto end = format.find('}', pos);

    if (end == std::string::npos)
        throw util::FormatException("Format specifier has no closing '}'-bracket!");

    util::SetupStreamByPrintfFormat(buf, format.substr(pos + 1, end - pos - 1));

    return end;
}

template<typename TIterator, typename ... TArgs>
void Format(const TIterator& begin, const TIterator& end, const TArgs& ...args) {

	if constexpr (is_iterator<TIterator>::value) {
		std::cout << "Printing iterators\n";
	}
	else {
		std::cout << "Printing normal values of same type\n";
	}

	Format(args...);
}

template <class T>
size_t WriteArray(const std::string &format, std::stringstream &buf, size_t pos, const T &arg)
{
    auto end = format.find(']', pos);

    if (end == std::string::npos)
        throw util::FormatException("Array specifier has no closing ']'-bracket!");

    return end;
}

template <class T>
size_t WriteArray(const std::string &format, std::stringstream &buf, size_t pos, const T *&arg)
{
    auto start = pos;
    auto end = format.find(']', pos);

    if (end == std::string::npos)
        throw util::FormatException("Array specifier has no closing ']'-bracket!");

    const auto access = ComputeArrayAccess(format.substr(start + 1, end - start - 1));

    for (size_t i = access.start; i < access.end; i += access.step)
        buf << arg[i];

    return end;
}

template <class T>
size_t WriteIterable(const std::string &format, std::stringstream &buf, size_t pos, const T &arg)
{
    auto start = pos;
    auto end = format.find('>', pos);

    if (end == std::string::npos)
        throw util::FormatException("Iterable specifier has no closing '>'-bracket!");

    const auto access = ComputeArrayAccess(format.substr(start + 1, end - start - 1));

    auto it = arg.begin();
    auto itEnd = arg.end();
    size_t i = 0;

    for (; i < access.start; i++)
        ++it;

    while (i < access.end)
    {
        if ((i - access.start) % access.step == 0)
            buf << *it;

        i++;
    }

    return end;
}

void FormatInternal(const std::string &format, std::stringstream &buf, size_t pos)
{
    while (pos < format.length() - 1)
    {
        if (format[pos] == '%')
        {
            throw util::FormatException("Format placeholder without too few arguments!");
        }
        else if (format[pos] == '\\')
        {
            buf << format[pos + 1];
            pos += 2;
        }
        else
        {
            buf << format[pos];
            pos++;
        }
    }

    if (pos < format.length())
    {
        if (format.back() == '%')
            throw util::FormatException("Format placeholder without too few arguments!");
        else
            buf << format.back();
    }
}

template <class TFirst, class... TArgs>
void FormatInternal(const std::string &format, std::stringstream &buf, size_t pos, const TFirst &firstArg, const TArgs &... args)
{
    while (pos < format.length() - 1)
    {
        if (format[pos] == '%')
        {
            if (format[pos + 1] == '{')
                pos = PrepareFormat(format, buf, pos + 1);

            if (format[pos + 1] == '[')
                pos = WriteArray(format, buf, pos + 1, firstArg);
            // else if (format[pos + 1] == '<')
            //     pos = WriteIterable(format, buf, pos + 1, firstArg);
            else
                buf << firstArg;

            FormatInternal(format, buf, pos + 1, args...);

            return;
        }
        else if (format[pos] == '\\')
        {
            buf << format[pos + 1];
            pos += 2;
        }
        else
        {
            buf << format[pos];
            pos++;
        }
    }

    if (pos < format.length())
    {
        if (format.back() == '%')
            buf << firstArg;
        else
            buf << format.back();
    }
}
} // namespace

template <class TFirst, class... TArgs>
std::string util::Format(const std::string &format, const TFirst &firstArg, const TArgs &... args)
{
    if (format.empty())
    {
        return std::string("");
    }

    std::stringstream buf;

    FormatInternal(format, buf, 0, firstArg, args...);

    return buf.str();
}