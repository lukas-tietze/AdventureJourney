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

int util::color::alpha() const
{
    return (this->data >> A_SHIFT) & LOW_BYTE_MASK;
}

int util::color::red() const
{
    return (this->data >> R_SHIFT) & LOW_BYTE_MASK;
}

int util::color::green() const
{
    return (this->data >> G_SHIFT) & LOW_BYTE_MASK;
}

int util::color::blue() const
{
    return (this->data >> B_SHIFT) & LOW_BYTE_MASK;
}

int util::color::value() const
{
    return this->data;
}

float util::color::alpha_percentage() const
{
    return this->alpha() / 255.0;
}

float util::color::red_percentage() const
{
    return this->red() / 255.0;
}

float util::color::green_percentage() const
{
    return this->green() / 255.0;
}

float util::color::blue_percentage() const
{
    return this->blue() / 255.0;
}

bool util::operator==(const util::color &c1, const util::color &c2)
{
    return c1.data == c2.data;
}

bool util::operator!=(const util::color &c1, const util::color &c2)
{
    return c1.data == c2.data;
}
