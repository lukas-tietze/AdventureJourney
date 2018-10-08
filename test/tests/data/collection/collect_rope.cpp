#include "data/collection/collect_rope.hpp"
#include "test.hpp"

int test::data_test::collection_test::test_collect_rope()
{
    auto rope = new util::collect_rope<int>();

    for (int i = 0; i < 1000; i++)
    {
        rope->push_back(i);
    }

    int i = 0;

    ////Automatic Iterator
    for (const auto &item : *rope)
    {
        assert::are_equal(i, item);
        i++;
    }

    i = 0;
    ////Manual Iterator
    for (const auto &pos = rope->begin(), end = rope->end(); pos != end; pos++)
    {
        assert::are_equal(i, *pos);
        i++;
    }

    return 0;
}