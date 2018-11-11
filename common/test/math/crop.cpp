#include "common/test/test_list.hpp"
#include "test.hpp"
#include "data/math.hpp"

int test::math_test::test_crop()
{
    assert::are_equal(5, util::crop(1, 5, 10));
    assert::are_equal(5, util::crop(2, 5, 10));
    assert::are_equal(5, util::crop(3, 5, 10));
    assert::are_equal(5, util::crop(4, 5, 10));
    assert::are_equal(5, util::crop(5, 5, 10));
    assert::are_equal(6, util::crop(6, 5, 10));
    assert::are_equal(7, util::crop(7, 5, 10));
    assert::are_equal(8, util::crop(8, 5, 10));
    assert::are_equal(9, util::crop(9, 5, 10));
    assert::are_equal(10, util::crop(10, 5, 10));
    assert::are_equal(10, util::crop(11, 5, 10));
    assert::are_equal(10, util::crop(12, 5, 10));
    assert::are_equal(10, util::crop(13, 5, 10));
    assert::are_equal(10, util::crop(14, 5, 10));
    assert::are_equal(10, util::crop(15, 5, 10));

    return 0;
}