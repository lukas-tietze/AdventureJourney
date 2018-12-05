#include "common/test/TestList.hpp"
#include "Test.hpp"
#include "data/Math.hpp"

int test::mathTest::TestCrop()
{
    assert::AreEqual(5, util::Crop(1, 5, 10));
    assert::AreEqual(5, util::Crop(2, 5, 10));
    assert::AreEqual(5, util::Crop(3, 5, 10));
    assert::AreEqual(5, util::Crop(4, 5, 10));
    assert::AreEqual(5, util::Crop(5, 5, 10));
    assert::AreEqual(6, util::Crop(6, 5, 10));
    assert::AreEqual(7, util::Crop(7, 5, 10));
    assert::AreEqual(8, util::Crop(8, 5, 10));
    assert::AreEqual(9, util::Crop(9, 5, 10));
    assert::AreEqual(10, util::Crop(10, 5, 10));
    assert::AreEqual(10, util::Crop(11, 5, 10));
    assert::AreEqual(10, util::Crop(12, 5, 10));
    assert::AreEqual(10, util::Crop(13, 5, 10));
    assert::AreEqual(10, util::Crop(14, 5, 10));
    assert::AreEqual(10, util::Crop(15, 5, 10));

    return 0;
}