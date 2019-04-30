#include "Test.hpp"
#include "libCommon/test/TestList.hpp"
#include "data/collection/CollectRope.hpp"

int test::dataTest::collectionTest::TestCollectRope()
{
    auto rope = new util::CollectRope<int, 10>();

    for (int i = 0; i < 1000; i++)
    {
        rope->Push(i);
    }

    assert::AreEqual((size_t)1000, rope->Size());
    assert::AreEqual((size_t)((1000 + rope->PartSize() - 1) / rope->PartSize()), rope->Parts());

    int i = 0;
    ////Automatic Iterator
    for (const auto &item : *rope)
    {
        assert::AreEqual(i, item);
        i++;
    }

    assert::AreEqual(1000, i);

    i = 0;
    ////Manual iterator with x++
    for (auto pos = rope->begin(), end = rope->end(); pos != end; pos++)
    {
        assert::AreEqual(i, *pos);
        i++;
    }

    assert::AreEqual(1000, i);

    i = 0;
    ////Manual iterator with ++x
    for (auto pos = rope->begin(), end = rope->end(); pos != end; ++pos)
    {
        assert::AreEqual(i, *pos);
        i++;
    }

    assert::AreEqual(1000, i);

    return 0;
}