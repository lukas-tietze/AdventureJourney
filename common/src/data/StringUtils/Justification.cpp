#include "data/String.hpp"
#include "data/Io.hpp"

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
    util::Channel log = util::Channel(std::fopen(util::Format("debugfiles/justificationLog%", std::time(nullptr)).c_str(), "w"));

    const size_t n = text.length();
    size_t i = 0;
    size_t lastLineBreak = 0;
    size_t nextWordEnd = 0;
    char c;

    log.WriteLine("Processing \"%\"", text);

    while (i < n)
    {
        nextWordEnd = FindWordEnd(text, i, args);

        log.WriteLine("Found word end from % at %.", i, nextWordEnd);

        if (nextWordEnd - lastLineBreak > maxLen)
        {
            buf.push_back(text.substr(lastLineBreak, nextWordEnd - lastLineBreak));
            lastLineBreak = nextWordEnd;

            log.WriteLine("Breaking line due to overflow at %.", lastLineBreak);
            log.WriteLine("Flushed line \"%\"", buf.back());
        }

        i = nextWordEnd + 1;

        log.WriteLine("handling spaces after %", i);

        while (i < n && std::isspace(text[i]))
        {
            c = text[i];

            if (c == '\n')
            {
                log.WriteLine("Creating line break after \\n at %", i);

                buf.push_back(text.substr(lastLineBreak, i - lastLineBreak));
                lastLineBreak = i;

                log.WriteLine("Flushed line \"%\"", buf.back());
            }

            i++;
        }
    }

    if (lastLineBreak < n)
    {
        buf.push_back(text.substr(lastLineBreak, n - lastLineBreak));
    }

    return buf;
}
