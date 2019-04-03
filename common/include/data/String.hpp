#pragma once

#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <list>
#include <sstream>
#include <Exception.hpp>
#include <ctime>

namespace util
{
struct JustificationArgs
{
    bool trimLines;
    bool trimMultipleSpaces;
    bool filterCariageReturns;
    bool filterBackspace;
    bool filterFormFeed;
    bool convertFormFeedToLineFeed;
    bool filterTabs;
    bool filterVerticalTab;
    bool convertVerticalTabToLineFeed;
    bool convertTabsToSpaces;
    uint32_t tabLen;
    uint32_t verticalTabLen;
    uint32_t formFeedLength;
};

extern JustificationArgs defaultJustificationArgs;

std::vector<std::string> Justify(const std::string &, int, const JustificationArgs & = defaultJustificationArgs);
std::vector<std::string> &Justify(const std::string &, int, std::vector<std::string> &, const JustificationArgs & = defaultJustificationArgs);

std::string Format2(const std::string &format, ...);

std::string ToUpper(const std::string &nameBuf);
std::string ToLower(const std::string &nameBuf);
std::string &ToUpperInplace(std::string &nameBuf);
std::string &ToLowerInplace(std::string &nameBuf);

std::vector<std::string> Split(const std::string &str, bool removeEmtpyEntries = false);
std::vector<std::string> Split(const std::string &str, char seperator, bool removeEmtpyEntries = false);
std::vector<std::string> Split(const std::string &str, const std::string &chars, bool removeEmtpyEntries = false);
std::vector<std::string> Split(const std::string &str, bool (*)(char), bool removeEmtpyEntries = false);
std::vector<std::string> &Split(const std::string &str, std::vector<std::string> &buf, bool removeEmtpyEntries = false);
std::vector<std::string> &Split(const std::string &str, std::vector<std::string> &buf, char seperator, bool removeEmtpyEntries = false);
std::vector<std::string> &Split(const std::string &str, std::vector<std::string> &buf, const std::string &chars, bool removeEmtpyEntries = false);
std::vector<std::string> &Split(const std::string &str, std::vector<std::string> &buf, bool (*)(char), bool removeEmtpyEntries = false);

std::string Strip(const std::string &);
std::string StripFront(const std::string &);
std::string StripBack(const std::string &);
std::string &StripInplace(std::string &);
std::string &StripFrontInplace(std::string &);
std::string &StripBackInplace(std::string &);

std::string Unescape(char);
std::string UtfCodePointToNarrowString(uint32_t);

class TimeFormatException : public util::Exception
{
  public:
    TimeFormatException(const std::string &, std::time_t);
};

std::string FormatLocalTime(const std::string &format);
std::string FormatLocalTime(const std::string &format, std::time_t);

uint32_t Hex4ToNumber(const std::string &);
uint32_t Hex4ToNumber(const char *);
uint8_t HexToNumber(char);
uint8_t HexToNumber(char, char);
uint32_t HexToNumber(const std::string &);
uint32_t HexToNumber(const char *);
bool IsHexChar(char);

template <class T>
std::string ToString(const T &arg)
{
    std::stringstream s;

    s << arg;

    return s.str();
}

template <class T>
T Parse(const std::string &value)
{
    return T();
}

template <typename NumT>
bool ParseIntegral(const std::string &text, NumT &target)
{
    try
    {
        target = static_cast<NumT>(std::stol(text));
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
    catch (const std::out_of_range &e)
    {
        return false;
    }

    return true;
}

template <typename NumT>
bool ParseFloat(const std::string &text, NumT &target)
{
    try
    {
        target = static_cast<NumT>(std::stod(text));
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
    catch (const std::out_of_range &e)
    {
        return false;
    }

    return true;
}

class FormatException : public util::Exception
{
  public:
    FormatException(const std::string &what);
};

void SetupStreamByPrintfFormat(std::iostream &, const std::string &);

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

    SetupStreamByPrintfFormat(buf, format.substr(pos + 1, end - pos - 1));

    return end;
}

template <class T>
size_t WriteArray(const std::string &format, std::stringstream &buf, size_t pos, const T &arg)
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
            throw FormatException("Format placeholder without too few arguments!");
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
            throw FormatException("Format placeholder without too few arguments!");
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

            // if (format[pos + 1] == '[')
            //     pos = WriteArray(format, buf, pos + 1, firstArg);
            // else if (format[pos + 1] == '<')
            //     pos = WriteIterable(format, buf, pos + 1, firstArg);
            // else
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
std::string Format(const std::string &format, const TFirst &firstArg, const TArgs &... args)
{
    if (format.empty())
    {
        return std::string("");
    }

    std::stringstream buf;

    FormatInternal(format, buf, 0, firstArg, args...);

    return buf.str();
}

namespace
{
template <class TIterator>
void PrintSequence(std::ostream &s, TIterator pos, TIterator end)
{
    s << '{';

    if (pos != end)
        s << ' ' << *pos;

    while (++pos != end)
        s << ", " << *pos;

    s << " }";
}

template <class TIterator>
void PrintSequenceOfPairs(std::ostream &s, TIterator pos, TIterator end)
{
    s << '{';

    if (pos != end)
        s << ' ' << pos->first << "=>" << pos->second;

    while (++pos != end)
        s << ", " << pos->first << "=>" << pos->second;

    s << " }";
}

// template<int pos, class ...Ts>
// void PrintTuple(std::ostream &, const std::tuple<Ts...> &tuple)
// {
//     std::get<pos>
// }
} // namespace

template <class T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &vector)
{
    PrintSequence(s, vector.begin(), vector.end());

    return s;
}

template <class T>
std::ostream &operator<<(std::ostream &s, const std::list<T> &list)
{
    PrintSequence(s, list.begin(), list.end());

    return s;
}

template <class TKey, class TValue>
std::ostream &operator<<(std::ostream &s, const std::map<TKey, TValue> &map)
{
    PrintSequenceOfPairs(s, map.begin(), map.end());

    return s;
}

// template <class... Ts>
// std::ostream &operator<<(std::ostream &s, const std::tuple<Ts...> &)
// {

// }
} // namespace util