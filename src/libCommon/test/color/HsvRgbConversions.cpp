#include "Test.hpp"
#include "libCommon/test/TestList.hpp"
#include "graphics/Color.hpp"

namespace
{
void TestIdentity(uint8_t r, uint8_t g, uint8_t b)
{
    auto c = util::Color(r, g, b);

    double h, s, v;

    c.AsHSV(h, s, v);

    assert::AreEqual(c, util::Color::FromHSV(h, s, v));
}
} // namespace

int test::colorTest::HsvRgbConversions()
{
    assert::AreEqual(util::Color(0, 0, 0), util::Color::FromHSV(0.0, 0.0, 0.0));
    assert::AreEqual(util::Color(255, 255, 255), util::Color::FromHSV(0.0, 0.0, 1.0));
    assert::AreEqual(util::Color(255, 0, 0), util::Color::FromHSV(0.0, 1.0, 1.0));
    assert::AreEqual(util::Color(0, 255, 0), util::Color::FromHSV(120.0, 1.0, 1.0));
    assert::AreEqual(util::Color(0, 0, 255), util::Color::FromHSV(240.0, 1.0, 1.0));
    assert::AreEqual(util::Color(255, 255, 0), util::Color::FromHSV(60.0, 1.0, 1.0));
    assert::AreEqual(util::Color(0, 255, 255), util::Color::FromHSV(180.0, 1.0, 1.0));
    assert::AreEqual(util::Color(255, 0, 255), util::Color::FromHSV(300.0, 1.0, 1.0));
    assert::AreEqual(util::Color(191, 191, 191), util::Color::FromHSV(0.0, 0.0, 0.75));
    assert::AreEqual(util::Color(128, 128, 128), util::Color::FromHSV(0.0, 0.0, 0.5f));
    assert::AreEqual(util::Color(128, 0, 0), util::Color::FromHSV(0.0, 1.0, 0.5f));
    assert::AreEqual(util::Color(128, 128, 0), util::Color::FromHSV(60.0, 1.0, 0.5f));
    assert::AreEqual(util::Color(0, 128, 0), util::Color::FromHSV(120.0, 1.0, 0.5f));
    assert::AreEqual(util::Color(128, 0, 128), util::Color::FromHSV(300.0, 1.0, 0.5f));
    assert::AreEqual(util::Color(0, 128, 128), util::Color::FromHSV(180.0, 1.0, 0.5f));
    assert::AreEqual(util::Color(0, 0, 128), util::Color::FromHSV(240.0, 1.0, 0.5f));

    TestIdentity(123, 244, 209);
    TestIdentity(5, 33, 223);
    TestIdentity(42, 0, 255);
    TestIdentity(190, 2, 0);
    TestIdentity(151, 93, 213);

	return 0;
}