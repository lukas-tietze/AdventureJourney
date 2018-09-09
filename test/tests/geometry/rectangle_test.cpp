#include "geometry.hpp"
#include "test.hpp"

int test::geometry_test::test_rectangle()
{
    util::rectangle r(0, 0, 10, 10);
    
    assert::is_true(r.contains(util::point(5, 5)));
    assert::is_true(r.contains(util::point(0, 0)));
    assert::is_true(r.contains(util::point(10, 0)));
    assert::is_true(r.contains(util::point(10, 10)));
    assert::is_true(r.contains(util::point(0, 10)));
    assert::is_false(r.contains(util::point(20, 5)));
    assert::is_false(r.contains(util::point(5, 20)));
    assert::is_false(r.contains(util::point(20, 20)));

    assert::are_equal(util::rectangle(0, 0, 5, 5), r.intersect(util::rectangle(-5, -5, 10, 10)));
    assert::are_equal(util::rectangle(5, 0, 5, 5), r.intersect(util::rectangle(5, -5, 10, 10)));
    assert::are_equal(util::rectangle(5, 5, 5, 5), r.intersect(util::rectangle(5, 5, 10, 10)));
    assert::are_equal(util::rectangle(0, 5, 5, 5), r.intersect(util::rectangle(5, -5, 10, 10)));

    return 0;
}