#include "terminal/controls/ControlBase.hpp"

terminal::Border::Border()
{
    this->styles[0] = COLOR_PAIR(1);
    this->styles[1] = COLOR_PAIR(1);
    this->styles[2] = COLOR_PAIR(1);
    this->styles[3] = COLOR_PAIR(1);

    this->sizes[0] = 1;
    this->sizes[1] = 1;
    this->sizes[2] = 1;
    this->sizes[3] = 1;
}

void terminal::Border::SetSize(uint8_t size)
{
    this->sizes[0] = size;
    this->sizes[1] = size;
    this->sizes[2] = size;
    this->sizes[3] = size;
}

void terminal::Border::SetStyle(int style)
{
    this->styles[0] = style;
    this->styles[1] = style;
    this->styles[2] = style;
    this->styles[3] = style;
}

void terminal::Border::SetTopSize(uint8_t size)
{
    this->sizes[0] = size;
}

void terminal::Border::SetTopStyle(int style)
{
    this->styles[0] = style;
}

void terminal::Border::SetRightSize(uint8_t size)
{
    this->sizes[1] = size;
}

void terminal::Border::SetRightStyle(int style)
{
    this->styles[1] = style;
}

void terminal::Border::SetBottomSize(uint8_t size)
{
    this->sizes[2] = size;
}

void terminal::Border::SetBottomStyle(int style)
{
    this->styles[2] = style;
}

void terminal::Border::SetLeftSize(uint8_t size)
{
    this->sizes[3] = size;
}

void terminal::Border::SetLeftStyle(int style)
{
    this->styles[3] = style;
}

uint8_t terminal::Border::GetTopSize()
{
    return this->sizes[0];
}

int terminal::Border::GetTopStyle()
{
    return this->styles[0];
}

uint8_t terminal::Border::GetRightSize()
{
    return this->sizes[1];
}

int terminal::Border::GetRightStyle()
{
    return this->styles[1];
}

uint8_t terminal::Border::GetBottomSize()
{
    return this->sizes[2];
}

int terminal::Border::GetBottomStyle()
{
    return this->styles[2];
}

uint8_t terminal::Border::GetLeftSize()
{
    return this->sizes[1];
}

int terminal::Border::GetLeftStyle()
{
    return this->styles[1];
}

void terminal::Border::Render(const util::Rectangle &bounds, Canvas &c)
{
    if (this->sizes[0] > 0)
    {
        c.SetActiveColorPair(this->styles[0]);

        for (int w = 0; w < this->sizes[0]; w++)
            c.DrawHorizontalLine(bounds.GetMinX(), bounds.GetMinY() + w, bounds.GetWidth(), '-');
    }

    if (this->sizes[1] > 0)
    {
        c.SetActiveColorPair(this->styles[1]);

        for (int w = 0; w < this->sizes[1]; w++)
            c.DrawVerticalLine(bounds.GetMaxX() - w, bounds.GetMinY(), bounds.GetHeight(), '|');
    }

    if (this->sizes[2] > 0)
    {
        c.SetActiveColorPair(this->styles[2]);

        for (int w = 0; w < this->sizes[2]; w++)
            c.DrawHorizontalLine(bounds.GetMinX(), bounds.GetMaxY() - w, bounds.GetWidth(), '-');
    }

    if (this->sizes[3] > 0)
    {
        c.SetActiveColorPair(this->styles[3]);

        for (int w = 0; w < this->sizes[3]; w++)
            c.DrawVerticalLine(bounds.GetMaxX() + w, bounds.GetMinY(), bounds.GetHeight(), '|');
    }
}
