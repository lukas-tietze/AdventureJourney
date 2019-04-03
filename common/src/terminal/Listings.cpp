#include "data/EnumHelper.hpp"
#include "terminal/controls/ControlBase.hpp"

template <>
const std::initializer_list<terminal::AutoSizeMode> &util::ListValues<terminal::AutoSizeMode>()
{
    static const std::initializer_list<terminal::AutoSizeMode> res = {
        terminal::AutoSizeMode::None,
        terminal::AutoSizeMode::Fill,
        terminal::AutoSizeMode::FillVertical,
        terminal::AutoSizeMode::FillHorizontal,
    };

    return res;
}

template <>
const std::initializer_list<terminal::BorderType> &util::ListValues<terminal::BorderType>()
{
    static const std::initializer_list<terminal::BorderType> res = {
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

    return res;
}