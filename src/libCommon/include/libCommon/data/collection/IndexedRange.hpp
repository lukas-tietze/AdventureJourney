#pragma once

namespace util
{
template <typename TIterator, typename TIndex = int>
class IndexedRange
{
public:
    IndexedRange(TIterator begin, TITerator end);

    class Iterator
    {
    private:
        TIterator pos;
        TIndex index;

    public:
        auto &operator*()
        {
            return [index, *(this->pos)];
        }
    };

    class ConstIterator
    {
        const auto &operator*()
        {
            return *(this->pos);
        }
    };
};
} // namespace util