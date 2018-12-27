#include "Test.hpp"
#include "common/test/TestList.hpp"
#include "Geometry.hpp"

int test::geometryTest::TestRectangle()
{
    util::Rectangle r(1, 2, 4, 5);

    assert::AreEqual(1, r.GetX());
    assert::AreEqual(1, r.GetMinX());
    assert::AreEqual(2, r.GetY());
    assert::AreEqual(2, r.GetMinY());
    assert::AreEqual(5, r.GetMaxX());
    assert::AreEqual(7, r.GetMaxY());
    assert::AreEqual(4, r.GetWidth());
    assert::AreEqual(5, r.GetHeight());
    assert::AreEqual(util::Point(1, 2), r.GetLocation());
    assert::AreEqual(util::Dimension(4, 5), r.GetSize());
    assert::AreEqual(4 * 5, r.GetArea());

    r = util::Rectangle(0, 0, 10, 10);

    assert::IsTrue(r.Contains(util::Point(5, 5)));
    assert::IsTrue(r.Contains(util::Point(0, 0)));
    assert::IsTrue(r.Contains(util::Point(10, 0)));
    assert::IsTrue(r.Contains(util::Point(10, 10)));
    assert::IsTrue(r.Contains(util::Point(0, 10)));
    assert::IsFalse(r.Contains(util::Point(20, 5)));
    assert::IsFalse(r.Contains(util::Point(5, 20)));
    assert::IsFalse(r.Contains(util::Point(20, 20)));

    assert::AreEqual(util::Point(5, 5), r.Fit(util::Point(5, 5)));
    assert::AreEqual(util::Point(0, 4), r.Fit(util::Point(-6, 4)));
    assert::AreEqual(util::Point(0, 10), r.Fit(util::Point(-8, 20)));
    assert::AreEqual(util::Point(7, 10), r.Fit(util::Point(7, 32)));
    assert::AreEqual(util::Point(10, 10), r.Fit(util::Point(50, 31)));
    assert::AreEqual(util::Point(10, 4), r.Fit(util::Point(12, 4)));
    assert::AreEqual(util::Point(10, 0), r.Fit(util::Point(41, -5)));
    assert::AreEqual(util::Point(3, 0), r.Fit(util::Point(3, -19)));

    assert::IsTrue(r.HasIntersection(util::Rectangle(3, 3, 4, 4)));
    assert::IsTrue(r.HasIntersection(util::Rectangle(-5, -5, 6, 6)));
    assert::IsTrue(r.HasIntersection(util::Rectangle(9, 9, 4, 4)));
    assert::IsTrue(r.HasIntersection(util::Rectangle(-5, -5, 20, 20)));
    assert::IsFalse(r.HasIntersection(util::Rectangle(11, 3, 4, 4)));
    assert::IsFalse(r.HasIntersection(util::Rectangle(3, 11, 4, 4)));
    assert::IsFalse(r.HasIntersection(util::Rectangle(-5, 3, 4, 4)));
    assert::IsFalse(r.HasIntersection(util::Rectangle(3, -5, 4, 4)));

    assert::AreEqual(util::Rectangle(0, 0, 5, 5), r.Intersect(util::Rectangle(-5, -5, 10, 10)));
    assert::AreEqual(util::Rectangle(5, 0, 5, 5), r.Intersect(util::Rectangle(5, -5, 10, 10)));
    assert::AreEqual(util::Rectangle(5, 5, 5, 5), r.Intersect(util::Rectangle(5, 5, 10, 10)));
    assert::AreEqual(util::Rectangle(0, 5, 5, 5), r.Intersect(util::Rectangle(-5, 5, 10, 10)));

    return 0;
}