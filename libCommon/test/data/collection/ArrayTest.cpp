#include <algorithm>

#include "Test.hpp"
#include "libCommon/test/TestList.hpp"
#include "data/collection/Array.hpp"

int test::dataTest::collectionTest::TestArray()
{
    util::Array<int> a(10);

    assert::AreEqual((size_t)10, a.Length());

    for (size_t i = 0; i < 10; i++)
    {
        a[i] = (int)i;
    }

    ////default iteration
    for (size_t i = 0; i < 10; i++)
    {
        assert::AreEqual((int)i, a[i]);
    }

    int i = 0;
    for (const auto &x : a)
    {
        assert::AreEqual(i, x);
        i++;
    }

    i = 0;
    for (auto pos = a.begin(), end = a.end(); pos != end; pos++)
    {
        assert::AreEqual(i, *pos);
        i++;
    }

    i = 0;
    for (auto pos = a.begin(), end = a.end(); pos != end; ++pos)
    {
        assert::AreEqual(i, *pos);
        i++;
    }

    i = 0;
    a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    for (auto pos = a.begin(), end = a.end(); pos != end; ++pos)
    {
        assert::AreEqual(i, *pos);
        i++;
    }

    return 0;
}