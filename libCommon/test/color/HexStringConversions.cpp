#include "Test.hpp"
#include "common/test/TestList.hpp"
#include "graphics/Color.hpp"

namespace
{
void TestIdentity(uint8_t r, uint8_t g, uint8_t b)
{
    auto c = util::Color(r, g, b);

    assert::AreEqual(c, util::Color::FromHexString(c.AsHex4String()));
    assert::AreEqual(c, util::Color::FromHexString(c.AsHex3String()));
}
} // namespace

int test::colorTest::HexStringConversions()
{
    util::Color color(255, 0, 255);

    assert::AreEqual(std::string("#ff00ffff"), color.AsHex4String());
    assert::AreEqual(std::string("#ff00ff"), color.AsHex3String());

    assert::AreEqual(util::Color(255, 255, 255, 255), util::Color::FromHexString("#fff"));
    assert::AreEqual(util::Color(255, 255, 255, 0), util::Color::FromHexString("#fff0"));
    assert::AreEqual(util::Color(255, 255, 255, 255), util::Color::FromHexString("#ffffff"));
    assert::AreEqual(util::Color(255, 255, 255, 0), util::Color::FromHexString("#ffffff00"));

    TestIdentity(123, 244, 209);
    TestIdentity(5, 33, 223);
    TestIdentity(42, 0, 255);
    TestIdentity(190, 2, 0);
    TestIdentity(151, 93, 213);

    return 0;
}
