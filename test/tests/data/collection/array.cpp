#include <algorithm>

#include "data/collection/array.hpp"
#include "test.hpp"

template <long FROM, long TO>
class Range
{
  public:
    // member typedefs provided through inheriting from std::iterator
    class iterator : public std::iterator<
                         std::input_iterator_tag, // iterator_category
                         long,                    // value_type
                         long,                    // difference_type
                         const long *,            // pointer
                         long                     // reference
                         >
    {
        long num = FROM;

      public:
        explicit iterator(long _num = 0) : num(_num) {}
        iterator &operator++()
        {
            num = TO >= FROM ? num + 1 : num - 1;
            return *this;
        }
        iterator operator++(int)
        {
            iterator retval = *this;
            ++(*this);
            return retval;
        }
        bool operator==(iterator other) const { return num == other.num; }
        bool operator!=(iterator other) const { return !(*this == other); }
        reference operator*() const { return num; }
    };
    iterator begin() { return iterator(FROM); }
    iterator end() { return iterator(TO >= FROM ? TO + 1 : TO - 1); }
};

int test::data_test::collection_test::test_array()
{
    auto range = Range<15, 25>();
    auto itr = std::find(range.begin(), range.end(), 18);

    return 0;
}