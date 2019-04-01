#include "data/EnumHelper.hpp"
#include "terminal/controls/ControlBase.hpp"

template <>
std::initializer_list<terminal::AutoSizeMode> util::ListValues<terminal::AutoSizeMode>()
{
    return {
        terminal::AutoSizeMode::None,
        terminal::AutoSizeMode::Fill,
        terminal::AutoSizeMode::FillVertical,
        terminal::AutoSizeMode::FillHorizontal,
    };
}

template <>
std::initializer_list<terminal::BorderType> util::ListValues<terminal::BorderType>()
{
    return {
        terminal::BorderType::TopEdge,
        terminal::BorderType::RightEdge,
        terminal::BorderType::BottomEdge,
        terminal::BorderType::LeftEdge,
        terminal::BorderType::TopLeftCorner,
        terminal::BorderType::TopRightCorner,
        terminal::BorderType::BottomRightCorner,
        terminal::BorderType::BottomLeftCorner,
        terminal::BorderType::TopLine,
        terminal::BorderType::BottomLine,
        terminal::BorderType::LeftLine,
        terminal::BorderType::RightLine,
        terminal::BorderType::AllEdges,
        terminal::BorderType::AllCorners,
        terminal::BorderType::All,
    };
}