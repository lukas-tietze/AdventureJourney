#include "test.hpp"
#include "graphics/color.hpp"

int test::color::test_basic_color_values()
{
    assert::are_equal(0, util::colors::BasicBlack.red(), "BasicBlack->red");
    assert::are_equal(0, util::colors::BasicBlack.green(), "BasicBlack->green");
    assert::are_equal(0, util::colors::BasicBlack.blue(), "BasicBlack->blue");
    assert::are_equal(255, util::colors::BasicBlack.alpha(), "BasicBlack->alpha");

    assert::are_equal(255, util::colors::BasicRed.red(), "BasicRed->red");
    assert::are_equal(0, util::colors::BasicRed.green(), "BasicRed->green");
    assert::are_equal(0, util::colors::BasicRed.blue(), "BasicRed->blue");
    assert::are_equal(255, util::colors::BasicRed.alpha(), "BasicRed->alpha");

    assert::are_equal(0, util::colors::BasicGreen.red(), "BasicGreen->red");
    assert::are_equal(255, util::colors::BasicGreen.green(), "BasicGreen->green");
    assert::are_equal(0, util::colors::BasicGreen.blue(), "BasicGreen->blue");
    assert::are_equal(255, util::colors::BasicGreen.alpha(), "BasicGreen->alpha");

    assert::are_equal(0, util::colors::BasicBlue.red(), "BasicBlue->red");
    assert::are_equal(0, util::colors::BasicBlue.green(), "BasicBlue->green");
    assert::are_equal(255, util::colors::BasicBlue.blue(), "BasicBlue->blue");
    assert::are_equal(255, util::colors::BasicBlue.alpha(), "BasicBlue->alpha");

    assert::are_equal(0, util::colors::BasicYellow.red(), "BasicYellow->red");
    assert::are_equal(255, util::colors::BasicYellow.green(), "BasicYellow->green");
    assert::are_equal(255, util::colors::BasicYellow.blue(), "BasicYellow->blue");
    assert::are_equal(255, util::colors::BasicYellow.alpha(), "BasicYellow->alpha");

    assert::are_equal(255, util::colors::BasicMagenta.red(), "BasicMagenta->red");
    assert::are_equal(0, util::colors::BasicMagenta.green(), "BasicMagenta->green");
    assert::are_equal(255, util::colors::BasicMagenta.blue(), "BasicMagenta->blue");
    assert::are_equal(255, util::colors::BasicMagenta.alpha(), "BasicMagenta->alpha");

    assert::are_equal(0, util::colors::BasicCyan.red(), "BasicCyan->red");
    assert::are_equal(255, util::colors::BasicCyan.green(), "BasicCyan->green");
    assert::are_equal(255, util::colors::BasicCyan.blue(), "BasicCyan->blue");
    assert::are_equal(255, util::colors::BasicCyan.alpha(), "BasicCyan->alpha");

    assert::are_equal(255, util::colors::BasicWhite.red(), "BasicWhite->red");
    assert::are_equal(255, util::colors::BasicWhite.green(), "BasicWhite->green");
    assert::are_equal(255, util::colors::BasicWhite.blue(), "BasicWhite->blue");
    assert::are_equal(255, util::colors::BasicWhite.alpha(), "BasicWhite->alpha");
}