#include "Test.hpp"
#include "libCommon/test/TestList.hpp"
#include "graphics/Color.hpp"

int test::colorTest::BasicColorValues()
{
    assert::AreEqual(0, util::colors::BasicBlack.Red());
    assert::AreEqual(0, util::colors::BasicBlack.Green());
    assert::AreEqual(0, util::colors::BasicBlack.Blue());
    assert::AreEqual(255, util::colors::BasicBlack.Alpha());

    assert::AreEqual(255, util::colors::BasicRed.Red());
    assert::AreEqual(0, util::colors::BasicRed.Green());
    assert::AreEqual(0, util::colors::BasicRed.Blue());
    assert::AreEqual(255, util::colors::BasicRed.Alpha());

    assert::AreEqual(0, util::colors::BasicGreen.Red());
    assert::AreEqual(255, util::colors::BasicGreen.Green());
    assert::AreEqual(0, util::colors::BasicGreen.Blue());
    assert::AreEqual(255, util::colors::BasicGreen.Alpha());

    assert::AreEqual(0, util::colors::BasicBlue.Red());
    assert::AreEqual(0, util::colors::BasicBlue.Green());
    assert::AreEqual(255, util::colors::BasicBlue.Blue());
    assert::AreEqual(255, util::colors::BasicBlue.Alpha());

    assert::AreEqual(255, util::colors::BasicYellow.Red());
    assert::AreEqual(255, util::colors::BasicYellow.Green());
    assert::AreEqual(0, util::colors::BasicYellow.Blue());
    assert::AreEqual(255, util::colors::BasicYellow.Alpha());

    assert::AreEqual(255, util::colors::BasicMagenta.Red());
    assert::AreEqual(0, util::colors::BasicMagenta.Green());
    assert::AreEqual(255, util::colors::BasicMagenta.Blue());
    assert::AreEqual(255, util::colors::BasicMagenta.Alpha());

    assert::AreEqual(0, util::colors::BasicCyan.Red());
    assert::AreEqual(255, util::colors::BasicCyan.Green());
    assert::AreEqual(255, util::colors::BasicCyan.Blue());
    assert::AreEqual(255, util::colors::BasicCyan.Alpha());

    assert::AreEqual(255, util::colors::BasicWhite.Red());
    assert::AreEqual(255, util::colors::BasicWhite.Green());
    assert::AreEqual(255, util::colors::BasicWhite.Blue());
    assert::AreEqual(255, util::colors::BasicWhite.Alpha());

    return 0;
}