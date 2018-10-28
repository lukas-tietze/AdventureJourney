#include "geometry.hpp"
#include "test.hpp"

int test::geometry_test::rectangle()
{
    util::rectangle r(1, 2, 4, 5);

    assert::are_equal(1, r.get_x());
    assert::are_equal(1, r.get_min_x());
    assert::are_equal(2, r.get_y());
    assert::are_equal(2, r.get_min_y());
    assert::are_equal(5, r.get_max_x());
    assert::are_equal(7, r.get_max_y());
    assert::are_equal(4, r.get_width());
    assert::are_equal(5, r.get_height());
    assert::are_equal(util::point(1, 2), r.get_location());
    assert::are_equal(util::dimension(4, 5), r.get_size());
    assert::are_equal(4 * 5, r.get_area());

    r = util::rectangle(0, 0, 10, 10);

    assert::is_true(r.contains(util::point(5, 5)));
    assert::is_true(r.contains(util::point(0, 0)));
    assert::is_true(r.contains(util::point(10, 0)));
    assert::is_true(r.contains(util::point(10, 10)));
    assert::is_true(r.contains(util::point(0, 10)));
    assert::is_false(r.contains(util::point(20, 5)));
    assert::is_false(r.contains(util::point(5, 20)));
    assert::is_false(r.contains(util::point(20, 20)));

    assert::are_equal(util::point(5, 5), r.fit(util::point(5, 5)));
    assert::are_equal(util::point(0, 4), r.fit(util::point(-6, 4)));
    assert::are_equal(util::point(0, 10), r.fit(util::point(-8, 20)));
    assert::are_equal(util::point(7, 10), r.fit(util::point(7, 32)));
    assert::are_equal(util::point(10, 10), r.fit(util::point(50, 31)));
    assert::are_equal(util::point(10, 4), r.fit(util::point(12, 4)));
    assert::are_equal(util::point(10, 0), r.fit(util::point(41, -5)));
    assert::are_equal(util::point(3, 0), r.fit(util::point(3, -19)));

    assert::is_true(r.has_intersection(util::rectangle(3, 3, 4, 4)));
    assert::is_true(r.has_intersection(util::rectangle(-5, -5, 6, 6)));
    assert::is_true(r.has_intersection(util::rectangle(9, 9, 4, 4)));
    assert::is_true(r.has_intersection(util::rectangle(-5, -5, 20, 20)));
    assert::is_false(r.has_intersection(util::rectangle(11, 3, 4, 4)));
    assert::is_false(r.has_intersection(util::rectangle(3, 11, 4, 4)));
    assert::is_false(r.has_intersection(util::rectangle(-5, 3, 4, 4)));
    assert::is_false(r.has_intersection(util::rectangle(3, -5, 4, 4)));

    assert::are_equal(util::rectangle(0, 0, 5, 5), r.intersect(util::rectangle(-5, -5, 10, 10)));
    assert::are_equal(util::rectangle(5, 0, 5, 5), r.intersect(util::rectangle(5, -5, 10, 10)));
    assert::are_equal(util::rectangle(5, 5, 5, 5), r.intersect(util::rectangle(5, 5, 10, 10)));
    assert::are_equal(util::rectangle(0, 5, 5, 5), r.intersect(util::rectangle(-5, 5, 10, 10)));

    return 0;
}