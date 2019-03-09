#include "data/String.hpp"

util::JustificationArgs util::defaultJustificationArgs = {

};

std::vector<std::string> util::Justify(const std::string &text, int maxLen, const JustificationArgs &args)
{
    std::vector<std::string> buf;

    util::Justify(text, maxLen, buf, args);

    return buf;
}

namespace
{
size_t FindWordEnd(const std::string &text, size_t startPos, const util::JustificationArgs &args)
{
}
} // namespace

std::vector<std::string> &util::Justify(const std::string &text, int maxLen, std::vector<std::string> &buf, const JustificationArgs &args)
{
    const int n = text.length();
    int i = 0;
    int lastBreak = 0;
    int lastLineBreak = 0;
    char c;

    buf.clear();

    while (i < n)
    {
        c = text[i];

        if (std::isspace(c) || i == n - 1)
        {
            if (i - lastBreak > maxLen)
            {
                buf.push_back(text.substr(lastLineBreak, maxLen));
                lastBreak = lastLineBreak + maxLen;

                while (i - lastBreak > maxLen)
                {
                    buf.push_back(text.substr(lastBreak, maxLen));
                    lastBreak += maxLen;
                }

                lastLineBreak = lastBreak;
            }
            else if (c == '\n' || i - lastLineBreak > maxLen)
            {
                buf.push_back(text.substr(lastLineBreak, i - lastLineBreak - 1));
                lastLineBreak = i + 1;
                lastBreak = i + 1;
            }
            else if (c == '\t')
            {
                //TODO!
            }
            else if (c == '\r')
            {
                //TODO ignorieren?
            }
        }

        i++;
    }

    if (args.trimLines)
    {
        for (auto &line : buf)
            util::StripInplace(line);
    }
}
