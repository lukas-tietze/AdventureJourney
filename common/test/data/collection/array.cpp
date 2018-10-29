#include <algorithm>

#include "test.hpp"
#include "../../test_list.hpp"
#include "data/collection/array.hpp"

int test::data_test::collection_test::test_array()
{
    util::array<int> a(10);

    assert::are_equal((size_t)10, a.length());

    for(size_t i = 0; i < 10; i++)
    {
        a[i] = (int)i;
    }

    ////default iteration
    for(size_t i = 0; i < 10; i++)
    {
        assert::are_equal((int)i, a[i]);
    }

    int i = 0;
    for(const auto &x : a)
    {
        assert::are_equal(i, x);
        i++;
    }

    i = 0;
    for(auto pos = a.begin(), end = a.end(); pos != end; pos++)
    {
        assert::are_equal(i, *pos);
        i++;
    }

    i = 0;
    for(auto pos = a.begin(), end = a.end(); pos != end; ++pos)
    {
        assert::are_equal(i, *pos);
        i++;
    }

    return 0;
}