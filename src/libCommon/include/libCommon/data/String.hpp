#pragma once

#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <list>
#include <sstream>
#include <ctime>
#include <limits>

#include "libCommon/Exception.hpp"

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
bool SplitKeyValue(const std::string &input, std::string &outKey, std::string &outValue);
std::pair<std::string, std::string> SplitKeyValue(const std::string &input);

std::string Strip(const std::string &);
std::string StripFront(const std::string &);
std::string StripBack(const std::string &);
std::string &StripInplace(std::string &);
std::string &StripFrontInplace(std::string &);
std::string &StripBackInplace(std::string &);

bool EndsWith(const std::string &str, const std::string &end);
bool StartsWith(const std::string &str, const std::string &start);
int OsaDistance(const std::string &s1, const std::string &s2);

char Escape(char);
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
std::string ToString(const T &arg);
template <class T>
T Parse(const std::string &value);
template <typename NumT>
bool ParseIntegral(const std::string &text, NumT &target);
template <typename NumT>
bool ParseFloat(const std::string &text, NumT &target);

class FormatException : public util::Exception
{
public:
    FormatException(const std::string &what);
};

void SetupStreamByPrintfFormat(std::iostream &, const std::string &);

template <class TFirst, class... TArgs>
std::string Format(const std::string &format, const TFirst &firstArg, const TArgs &... args);

template <class T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &vector);
template <class T>
std::ostream &operator<<(std::ostream &s, const std::list<T> &list);
template <class TKey, class TValue>
std::ostream &operator<<(std::ostream &s, const std::map<TKey, TValue> &map);

class String
{
private:
    char *start;
    uint32_t len;

public:
    static const String Empty;

    String();
    String(const std::string &);
    String(const char *);
    String(const std::string &, uint32_t len);
    String(const char *, uint32_t len);
    String(const std::string &, uint32_t start, uint32_t len);
    String(const char *, uint32_t start, uint32_t len);
    String(char c, uint32_t count);

    uint32_t Length() const;
    bool IsEmpty() const;

    bool Contains(const std::string &);
    bool Contains(const String &);
    bool Contains(const char *, int len = -1);
    bool StartsWith(const std::string &);
    bool StartsWith(const String &);
    bool StartsWith(const char *, int len = -1);
    bool EndsWith(const std::string &);
    bool EndsWith(const String &);
    bool EndsWith(const char *, int len = -1);
    String Concat(const std::string &);
    String Concat(const String &);
    String Concat(const char *, int len = -1);
    String &operator=(const std::string &);
    String &operator=(const String &);
    String &operator=(std::string &);
    String &operator=(String &);
    String Trim(char = ' ');
    String Trim(const char *, int = -1);
    String Trim(const std::string &);
    String Trim(const String &);
    String TrimStart(char = ' ');
    String TrimStart(const char *, int = -1);
    String TrimStart(const std::string &);
    String TrimStart(const String &);
    String TrimEnd(char = ' ');
    String TrimEnd(const char *, int = -1);
    String TrimEnd(const std::string &);
    String TrimEnd(const String &);

    String Substring(uint32_t start, uint32_t len = std::numeric_limits<uint32_t>::max());
};

std::ostream &operator<<(std::ostream &, const String &);

class StringBuilder
{
private:
    struct Node
    {
        Node *next;
        char *buf;
        uint32_t len;
    };

    Node *first;
    uint32_t totalLen;

public:
    StringBuilder();
    ~StringBuilder();

    StringBuilder &Append(const char *);
    StringBuilder &Append(const std::string &);
    StringBuilder &Append(const String &);
    StringBuilder &Append(const char *, uint32_t, uint32_t = std::numeric_limits<uint32_t>::max());
    StringBuilder &Append(const std::string &, uint32_t, uint32_t = std::numeric_limits<uint32_t>::max());
    StringBuilder &Append(const String &, uint32_t, uint32_t = std::numeric_limits<uint32_t>::max());
    StringBuilder &Append(int8_t);
    StringBuilder &Append(int16_t);
    StringBuilder &Append(int32_t);
    StringBuilder &Append(int64_t);
    StringBuilder &Append(uint8_t);
    StringBuilder &Append(uint16_t);
    StringBuilder &Append(uint32_t);
    StringBuilder &Append(uint64_t);
    StringBuilder &Append(float);
    StringBuilder &Append(double);
    StringBuilder &Append(long double);
    StringBuilder &AppendLine(const char *);
    StringBuilder &AppendLine(const std::string &);
    StringBuilder &AppendLine(const String &);
    StringBuilder &AppendLine(const char *, uint32_t, uint32_t = std::numeric_limits<uint32_t>::max());
    StringBuilder &AppendLine(const std::string &, uint32_t, uint32_t = std::numeric_limits<uint32_t>::max());
    StringBuilder &AppendLine(const String &, uint32_t, uint32_t = std::numeric_limits<uint32_t>::max());
    StringBuilder &AppendLine(int8_t);
    StringBuilder &AppendLine(int16_t);
    StringBuilder &AppendLine(int32_t);
    StringBuilder &AppendLine(int64_t);
    StringBuilder &AppendLine(uint8_t);
    StringBuilder &AppendLine(uint16_t);
    StringBuilder &AppendLine(uint32_t);
    StringBuilder &AppendLine(uint64_t);
    StringBuilder &AppendLine(float);
    StringBuilder &AppendLine(double);
    StringBuilder &AppendLine(long double);
    StringBuilder &AppendLine();
    StringBuilder &AppendFormat(const std::string &);

    String ToString();
    uint32_t Length();
};

std::ostream &operator<<(std::ostream &, const StringBuilder &);

class StringBuilderCache
{
private:
    static thread_local StringBuilder cachedInstance;

    StringBuilderCache();

public:
    static StringBuilder &Acquire();
    static void Release();
    static String CreateStringAndRelease();
};
} // namespace util

#include "libCommon/src/data/StringUtils/Format.inl"
#include "libCommon/src/data/StringUtils/StreamOperators.inl"
#include "libCommon/src/data/StringUtils/Conversions.inl"
