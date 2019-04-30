#include "data/String.hpp"

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