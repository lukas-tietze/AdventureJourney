#include "libCommon/test/TestList.hpp"
#include "data/Math.hpp"
#include "Test.hpp"

int test::mathTest::TestMax()
{
    assert::AreEqual(1, util::Max(0, 1));
    assert::AreEqual(2, util::Max(0, 1, 2));
    assert::AreEqual(3, util::Max(0, 1, 2, 3));
    assert::AreEqual(4, util::Max(0, 1, 2, 3, 4));
    assert::AreEqual(5, util::Max(0, 1, 2, 3, 4, 5));

    assert::AreEqual(5.5f, util::Max(5.5f, 1.0f, 2.f, 3.f, 4.f, 5.f));

	return 0;
}