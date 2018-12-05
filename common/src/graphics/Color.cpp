#include "graphics/Color.hpp"

util::Color::Color() : util::Color(0)
{
}

util::Color::Color(const util::Color &copy) : data(copy.data)
{
}

util::Color::Color(int r, int g, int b, int a) : data((static_cast<uint>(a) << A_SHIFT) |
                                                      (static_cast<uint>(r) << R_SHIFT) |
                                                      (static_cast<uint>(g) << G_SHIFT) |
                                                      (static_cast<uint>(b) << B_SHIFT))
{
}

util::Color::Color(float r, float g, float b, float a) : Color((int)(r * 255), (int)(g * 255), (int)(b * 255), (int)(a * 255))
{
}

util::Color::Color(uint Color) : data(Color)
{
}

int util::Color::Alpha() const
{
    return static_cast<int>((this->data >> A_SHIFT) & LOW_BYTE_MASK);
}

int util::Color::Red() const
{
    return static_cast<int>((this->data >> R_SHIFT) & LOW_BYTE_MASK);
}

int util::Color::Green() const
{
    return static_cast<int>((this->data >> G_SHIFT) & LOW_BYTE_MASK);
}

int util::Color::Blue() const
{
    return static_cast<int>((this->data >> B_SHIFT) & LOW_BYTE_MASK);
}

uint util::Color::Value() const
{
    return this->data;
}

float util::Color::AlphaPercentage() const
{
    return this->Alpha() / 255.0;
}

float util::Color::RedPercentage() const
{
    return this->Red() / 255.0;
}

float util::Color::GreenPercentage() const
{
    return this->Green() / 255.0;
}

float util::Color::BluePercentage() const
{
    return this->Blue() / 255.0;
}

bool util::operator==(const util::Color &c1, const util::Color &c2)
{
    return c1.Value() == c2.Value();
}

bool util::operator!=(const util::Color &c1, const util::Color &c2)
{
    return c1.Value() != c2.Value();
}
