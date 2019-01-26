#include "terminal/TerminalView.hpp"

namespace
{
terminal::controlStyles::ControlStyleColorPallette &Create()
{
    util::Array<util::Color> colors = {

    };
    util::Array<terminal::ColorPair> colorPairs = {

    };

    auto res = terminal::controlStyles::ControlStyleColorPallette(colors, colorPairs);

    return res;
}
} // namespace

terminal::controlStyles::ControlStyleColorPallette terminal::controlStyles::defaultFull = Create();