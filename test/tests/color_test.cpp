#include "test.hpp"
#include "graphics/color.hpp"

int test::color::test_basic_color_values()
{
    // assert::are_equal(0xFF000000, util::colors::BasicBlack.value());
    assert::are_equal(0, util::colors::BasicBlack.red());
    assert::are_equal(0, util::colors::BasicBlack.green());
    assert::are_equal(0, util::colors::BasicBlack.blue());
    assert::are_equal(255, util::colors::BasicBlack.alpha());

    assert::are_equal(255, util::colors::BasicRed.red());
    assert::are_equal(0, util::colors::BasicRed.green());
    assert::are_equal(0, util::colors::BasicRed.blue());
    assert::are_equal(255, util::colors::BasicRed.alpha());

    assert::are_equal(0, util::colors::BasicGreen.red());
    assert::are_equal(255, util::colors::BasicGreen.green());
    assert::are_equal(0, util::colors::BasicGreen.blue());
    assert::are_equal(255, util::colors::BasicGreen.alpha());

    assert::are_equal(0, util::colors::BasicBlue.red());
    assert::are_equal(0, util::colors::BasicBlue.green());
    assert::are_equal(255, util::colors::BasicBlue.blue());
    assert::are_equal(255, util::colors::BasicBlue.alpha());

    assert::are_equal(0, util::colors::BasicYellow.red());
    assert::are_equal(255, util::colors::BasicYellow.green());
    assert::are_equal(255, util::colors::BasicYellow.blue());
    assert::are_equal(255, util::colors::BasicYellow.alpha());

    assert::are_equal(255, util::colors::BasicMagenta.red());
    assert::are_equal(0, util::colors::BasicMagenta.green());
    assert::are_equal(255, util::colors::BasicMagenta.blue());
    assert::are_equal(255, util::colors::BasicMagenta.alpha());

    assert::are_equal(0, util::colors::BasicCyan.red());
    assert::are_equal(255, util::colors::BasicCyan.green());
    assert::are_equal(255, util::colors::BasicCyan.blue());
    assert::are_equal(255, util::colors::BasicCyan.alpha());

    assert::are_equal(255, util::colors::BasicWhite.red());
    assert::are_equal(255, util::colors::BasicWhite.green());
    assert::are_equal(255, util::colors::BasicWhite.blue());
    assert::are_equal(255, util::colors::BasicWhite.alpha());
}