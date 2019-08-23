#pragma once

#include <vector>

namespace util
{
namespace linq
{
class LinqTransform
{
};

template <class TIterator>
class LinqCollection
{
private:
    TIterator begin;
    TIterator end;
    std::vector<LinqTransform *> transformations;

public:
    LinqCollection(const TIterator &begin, const TIterator &end);

    LinqCollection &Select();
    LinqCollection &Where();
};

template <class TIterator>
LinqCollection<TIterator> Linq(const TIterator &begin, const TIterator &end);

template <class T>
LinqCollection<typename std::vector<T>::iterator> Linq(const std::vector<T> &);
} // namespace linq
} // namespace util
