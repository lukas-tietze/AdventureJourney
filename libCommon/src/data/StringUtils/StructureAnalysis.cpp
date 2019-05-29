#include "data/String.hpp"
#include "data/Math.hpp"

bool util::EndsWith(const std::string &str, const std::string &end)
{
    if (end.empty())
        return true;

    if (str.length() < end.length())
        return false;

    const size_t offset = str.length() - end.length();
    const size_t max = end.length();
    size_t i = 0;

    while (i < max && end[i] == str[offset + i])
        i++;

    return i == max;
}

bool util::StartsWith(const std::string &str, const std::string &start)
{
    if (start.empty())
        return true;

    if (str.length() < start.length())
        return false;

    const size_t max = start.length();
    size_t i = 0;

    while (i < max && start[i] == str[i])
        i++;

    return i == max;
}

int util::OsaDistance(const std::string &s1, const std::string &s2)
{
    auto d = new int[s1.length() + 1, s2.length() + 1];

    for (auto i = 0; i <= s1.length(); i++)
    {
        d[i, 0] = i;
    }

    for (auto i = 0; i <= s2.length(); i++)
    {
        d[0, i] = i;
    }

    for (auto i = 1; i <= s1.length(); i++)
    {
        for (auto j = 1; j <= s2.length(); j++)
        {
            auto cost = s1[i - 1] == s2[j - 1] ? 0 : 1;

            d[i, j] = util::Min(util::Min(d[i - 1, j] + 1,  // deletion
                                          d[i, j - 1] + 1), // insertion
                                d[i - 1, j - 1] + cost);    // substitution

            if (i > 2 && j > 2 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1])
            {
                d[i, j] = util::Min(d[i, j], d[i - 2, j - 2] + cost); // transposition
            }
        }
    }

    return d[s1.length(), s2.length()];
}