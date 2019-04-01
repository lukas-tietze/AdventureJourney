#include "data/Io.hpp"
#include "terminal/controls/ControlBase.hpp"

namespace
{
constexpr size_t TOP = 0;
constexpr size_t RIGHT = 1;
constexpr size_t BOTTOM = 2;
constexpr size_t LEFT = 3;
constexpr size_t TOP_LEFT = 4;
constexpr size_t TOP_RIGHT = 5;
constexpr size_t BOTTOM_RIGHT = 6;
constexpr size_t BOTTOM_LEFT = 7;
}; // namespace

terminal::Border::Border() : values({'-', '|', '-', '|', '+', '+', '+', '+'}),
                             styles({1, 1, 1, 1, 1, 1, 1, 1})
{
    // for (int i = 0; i < 8; i++)
    //     this->styles[i] = 0;
}

void terminal::Border::SetStyle(colorPairId_t value)
{
    util::dbg.WriteLine("Border [%]: Setting all styles to %", this, value);

    for (size_t i = 0; i < 8; i++)
        this->styles[i] = value;
}

void terminal::Border::SetStyle(BorderType type, colorPairId_t value)
{
    util::dbg.WriteLine("Border [%]: Setting style of % to %", this, type, value);

    for (size_t i = 0; i < 8; i++)
        if (static_cast<size_t>(type) & i != 0)
            this->styles[(i)] = value;
}

terminal::colorPairId_t terminal::Border::GetStyle(BorderType type) const
{
    return this->styles[static_cast<size_t>(type)];
}

void terminal::Border::SetChar(BorderType type, int value)
{
    for (size_t i = 0; i < 8; i++)
        if (static_cast<size_t>(type) & i != 0)
            this->values[(i)] = value;
}

int terminal::Border::GetChar(BorderType type) const
{
    return this->styles[static_cast<size_t>(type)];
}

void terminal::Border::SetEnabled(bool enabled)
{
    for (size_t i = 0; i < 8; i++)
        this->enabled[(i)] = enabled;
}

void terminal::Border::SetEnabled(BorderType type, bool enabled)
{
    for (size_t i = 0; i < 8; i++)
        if (static_cast<size_t>(type) & i != 0)
            this->enabled[(i)] = enabled;
}

bool terminal::Border::IsEnabled(BorderType type) const
{
    return this->enabled[static_cast<size_t>(type)];
}

void terminal::Border::Render(const util::Rectangle &bounds, terminal::Canvas &c)
{
    if (this->enabled[TOP])
    {
        c.SetActiveColorPair(this->styles[TOP]);
        c.DrawHorizontalLine(bounds.GetMinX() + 1, bounds.GetMinY(), bounds.GetWidth() - 2, this->values[TOP]);
    }

    if (this->enabled[RIGHT])
    {
        c.SetActiveColorPair(this->styles[RIGHT]);
        c.DrawVerticalLine(bounds.GetMaxX() - 1, bounds.GetMinY() + 1, bounds.GetHeight() - 2, this->values[RIGHT]);
    }

    if (this->enabled[BOTTOM])
    {
        c.SetActiveColorPair(this->styles[BOTTOM]);
        c.DrawHorizontalLine(bounds.GetMinX() + 1, bounds.GetMaxY() - 1, bounds.GetWidth() - 2, this->values[BOTTOM]);
    }

    if (this->enabled[LEFT])
    {
        c.SetActiveColorPair(this->styles[LEFT]);
        c.DrawVerticalLine(bounds.GetMinX(), bounds.GetMinY() + 1, bounds.GetHeight() - 2, this->values[LEFT]);
    }

    if (this->enabled[TOP_LEFT])
    {
        c.SetActiveColorPair(this->styles[TOP_LEFT]);
        c.DrawChar(bounds.GetMinX(), bounds.GetMinY(), this->values[TOP_LEFT]);
    }

    if (this->enabled[TOP_RIGHT])
    {
        c.SetActiveColorPair(this->styles[TOP_RIGHT]);
        c.DrawChar(bounds.GetMaxX() - 1, bounds.GetMinY(), this->values[TOP_RIGHT]);
    }

    if (this->enabled[BOTTOM_RIGHT])
    {
        c.SetActiveColorPair(this->styles[BOTTOM_RIGHT]);
        c.DrawChar(bounds.GetMaxX() - 1, bounds.GetMaxY() - 1, this->values[BOTTOM_RIGHT]);
    }

    if (this->enabled[BOTTOM_LEFT])
    {
        c.SetActiveColorPair(this->styles[BOTTOM_LEFT]);
        c.DrawChar(bounds.GetMinX(), bounds.GetMaxY() - 1, this->values[BOTTOM_LEFT]);
    }
}