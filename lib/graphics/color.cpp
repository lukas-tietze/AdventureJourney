#include "graphics/color.hpp"

util::color::color() : util::color(0)
{
}

util::color::color(const util::color &copy) : data(copy.data)
{
}

util::color::color(int r, int g, int b, int a) : data((a << A_SHIFT) | (r << R_SHIFT) | (g < G_SHIFT) | (b << B_SHIFT))
{
}

util::color::color(float r, float g, float b, float a) : color((int)(r * 255), (int)(g * 255), (int)(b * 255), (int)(a * 255))
{
}

util::color::color(int color) : data(color)
{
}

int util::color::alpha()
{
    return (this->data >> A_SHIFT) & LOW_BYTE_MASK;
}

int util::color::red()
{
    return (this->data >> R_SHIFT) & LOW_BYTE_MASK;
}

int util::color::green()
{
    return (this->data >> G_SHIFT) & LOW_BYTE_MASK;
}

int util::color::blue()
{
    return (this->data >> B_SHIFT) & LOW_BYTE_MASK;
}

int util::color::value()
{
    return this->data;
}