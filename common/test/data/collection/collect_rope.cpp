#include "test.hpp"
#include "../../test_list.hpp"
#include "data/collection/collect_rope.hpp"

int test::data_test::collection_test::test_collect_rope()
{
    auto rope = new util::collect_rope<int, 10>();

    for (int i = 0; i < 1000; i++)
    {
        rope->push_back(i);
    }

    assert::are_equal((size_t)1000, rope->size(), CPL_LOCATION);
    assert::are_equal((size_t)((1000 + rope->part_size() - 1) / rope->part_size()), rope->parts(), CPL_LOCATION);

    int i = 0;
    ////Automatic Iterator
    for (const auto &item : *rope)
    {
        assert::are_equal(i, item);
        i++;
    }

    assert::are_equal(1000, i);

    i = 0;
    ////Manual iterator with x++
    for (auto pos = rope->begin(), end = rope->end(); pos != end; pos++)
    {
        assert::are_equal(i, *pos);
        i++;
    }

    assert::are_equal(1000, i);

    i = 0;
    ////Manual iterator with ++x
    for (auto pos = rope->begin(), end = rope->end(); pos != end; ++pos)
    {
        assert::are_equal(i, *pos);
        i++;
    }

    assert::are_equal(1000, i);

    return 0;
}