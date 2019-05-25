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

bool EndsWith(const std::string &str, const std::string &end);
bool StartsWith(const std::string &str, const std::string &start);

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
} // namespace util

#include "libCommon/src/data/StringUtils/Format.inl"
#include "libCommon/src/data/StringUtils/StreamOperators.inl"
#include "libCommon/src/data/StringUtils/Conversions.inl"