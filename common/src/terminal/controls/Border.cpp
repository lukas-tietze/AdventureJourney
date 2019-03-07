#include "terminal/controls/ControlBase.hpp"

terminal::Border::Border() : values({'-', '|', '-', '|', '+', '+', '+', '+'}),
                             styles({0, 0, 0, 0, 0, 0, 0, 0})
{
}

void terminal::Border::SetStyle(colorPairId_t value)
{
    for (size_t i = 0; i < 8; i++)
        this->styles[i] = value;
}

void terminal::Border::SetStyle(BorderType type, colorPairId_t value)
{
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
        this->values[(i)] = enabled;
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
    if (this->enabled[static_cast<size_t>(BorderType::TopEdge)])
    {
        c.SetActiveColorPair(this->styles[static_cast<size_t>(BorderType::TopEdge)]);
        c.DrawHorizontalLine(bounds.GetMinX() + 1, bounds.GetMinY(), bounds.GetWidth() - 2, this->values[static_cast<size_t>(BorderType::TopEdge)]);
    }

    if (this->enabled[static_cast<size_t>(BorderType::RightEdge)])
    {
        c.SetActiveColorPair(this->styles[static_cast<size_t>(BorderType::RightEdge)]);
        c.DrawVerticalLine(bounds.GetMaxX() - 1, bounds.GetMinY() + 1, bounds.GetHeight() - 2, this->values[static_cast<size_t>(BorderType::RightEdge)]);
    }

    if (this->enabled[static_cast<size_t>(BorderType::BottomEdge)])
    {
        c.SetActiveColorPair(this->styles[static_cast<size_t>(BorderType::BottomEdge)]);
        c.DrawHorizontalLine(bounds.GetMinX() + 1, bounds.GetMaxY() - 1, bounds.GetWidth() - 2, this->values[static_cast<size_t>(BorderType::BottomEdge)]);
    }

    if (this->enabled[static_cast<size_t>(BorderType::LeftEdge)])
    {
        c.SetActiveColorPair(this->styles[static_cast<size_t>(BorderType::LeftEdge)]);
        c.DrawVerticalLine(bounds.GetMinX(), bounds.GetMinY() + 1, bounds.GetHeight() - 2, this->values[static_cast<size_t>(BorderType::RightEdge)]);
    }

    if (this->enabled[static_cast<size_t>(BorderType::TopLeftCorner)])
    {
        c.SetActiveColorPair(this->styles[static_cast<size_t>(BorderType::TopLeftCorner)]);
        c.DrawChar(bounds.GetMinX(), bounds.GetMinY(), this->values[static_cast<size_t>(BorderType::TopLeftCorner)]);
    }

    if (this->enabled[static_cast<size_t>(BorderType::TopRightCorner)])
    {
        c.SetActiveColorPair(this->styles[static_cast<size_t>(BorderType::TopRightCorner)]);
        c.DrawChar(bounds.GetMaxX() - 1, bounds.GetMinY(), this->values[static_cast<size_t>(BorderType::TopRightCorner)]);
    }

    if (this->enabled[static_cast<size_t>(BorderType::BottomRightCorner)])
    {
        c.SetActiveColorPair(this->styles[static_cast<size_t>(BorderType::BottomRightCorner)]);
        c.DrawChar(bounds.GetMaxX() - 1, bounds.GetMaxY() - 1, this->values[static_cast<size_t>(BorderType::BottomRightCorner)]);
    }

    if (this->enabled[static_cast<size_t>(BorderType::BottomLeftCorner)])
    {
        c.SetActiveColorPair(this->styles[static_cast<size_t>(BorderType::BottomLeftCorner)]);
        c.DrawChar(bounds.GetMinX(), bounds.GetMaxY() - 1, this->values[static_cast<size_t>(BorderType::BottomLeftCorner)]);
    }
}