#include "libCommon/data/String.hpp"

util::JustificationArgs util::defaultJustificationArgs = {
    // bool trimLines;
    false,
    // bool trimMultipleSpaces;
    false,
    // bool filterCariageReturns;
    true,
    // bool filterBackspace;
    true,
    // bool filterFormFeed;
    true,
    // bool convertFormFeedToLineFeed;
    false,
    // bool filterTabs;
    false,
    // bool filterVerticalTab;
    false,
    // bool convertVerticalTabToLineFeed;
    true,
    // bool convertTabsToSpaces;
    true,
    // uint32_t tabLen;
    4,
    // uint32_t verticalTabLen;
    3,
    // uint32_t formFeedLength;
    0,
};

std::vector<std::string> util::Justify(const std::string &text, int maxLen, const JustificationArgs &args)
{
    std::vector<std::string> buf;

    util::Justify(text, maxLen, buf, args);

    return buf;
}

namespace
{
size_t FindWordEnd(const std::string &text, size_t start, const util::JustificationArgs &args)
{
    auto i = start;

    while (i < text.length() && std::isalnum(text[i]))
        i++;

    return i;
}
} // namespace

std::vector<std::string> &util::Justify(const std::string &text, int maxLen, std::vector<std::string> &buf, const JustificationArgs &args)
{
    const size_t n = text.length();
    size_t i = 0;
    size_t lastLineBreak = 0;
    size_t nextWordEnd = 0;
    char c;

    while (i < n)
    {
        nextWordEnd = FindWordEnd(text, i, args);

        if (nextWordEnd - i > maxLen)
        {
            buf.push_back(text.substr(lastLineBreak, maxLen));
            i = lastLineBreak + maxLen;

            while (nextWordEnd - i > maxLen)
            {
                buf.push_back(text.substr(i, maxLen));
                i += maxLen;
            }

            lastLineBreak = i;
        }
        else if (nextWordEnd - lastLineBreak > maxLen)
        {
            buf.push_back(text.substr(lastLineBreak, i - lastLineBreak - 1));
            lastLineBreak = i;
        }

        i = nextWordEnd;

        if (!std::isspace(text[i]))
            i++;
        else
            while (i < n && std::isspace(text[i]))
            {
                c = text[i];

                if (c == '\n')
                {
                    buf.push_back(text.substr(lastLineBreak, i - lastLineBreak));
                    lastLineBreak = i + 1;
                }

                i++;
            }
    }

    if (lastLineBreak < n)
    {
        buf.push_back(text.substr(lastLineBreak));
    }

    return buf;
}
