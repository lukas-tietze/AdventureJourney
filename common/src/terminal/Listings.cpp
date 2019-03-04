#include "data/EnumHelper.hpp"
#include "terminal/controls/ControlBase.hpp"

template <>
std::initializer_list<terminal::AutoSizeMode> util::ListValues<terminal::AutoSizeMode>()
{
    return {
        terminal::AutoSizeMode::None,
        terminal::AutoSizeMode::Fill,
        terminal::AutoSizeMode::Fit,
    };
}

template <>
std::initializer_list<terminal::Alignment> util::ListValues<terminal::Alignment>()
{
    return {
        terminal::Alignment::Right,
        terminal::Alignment::Left,
        terminal::Alignment::Top,
        terminal::Alignment::Bottom,
        terminal::Alignment::Fill,
        terminal::Alignment::Absolute,
    };
}