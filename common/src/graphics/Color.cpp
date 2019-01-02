#include <cmath>
#include <iomanip>

#include "graphics/Color.hpp"
#include "data/collection/Array.hpp"
#include "data/Math.hpp"
#include "data/String.hpp"

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

std::ostream &util::operator<<(std::ostream &s, const util::Color &c)
{
    return s << c.AsHex4String();
}

void util::Color::AsHSV(float &hue, float &saturation, float &value)
{
    float r = this->RedPercentage();
    float g = this->GreenPercentage();
    float b = this->BluePercentage();

    float cMax = util::Max(r, g, b);
    float delta = cMax - util::Min(r, g, b);

    if (delta == 0)
    {
        hue = 0;
    }
    else if (cMax == r)
    {
        hue = 60.0f * util::Mod((g - b) / delta, 6.0f);
    }
    else if (cMax == g)
    {
        hue = 60.0f * (((b - r) / delta) + 2);
    }
    else if (cMax == b)
    {
        hue = 60.0f * (((r - g) / delta) + 4);
    }

    saturation = cMax != 0 ? delta / cMax : 0;

    value = cMax;
}

util::Color util::Color::FromHSV(float hue, float saturation, float value)
{
    hue = util::Mod(hue, 360.f);
    saturation = util::Crop(saturation, 0.f, 1.f);
    value = util::Crop(value, 0.f, 1.f);

    auto c = value * saturation;
    auto x = c * (1.f - std::abs(util::Mod(hue / 60.f, 2.f) - 1));

    util::Array<float> data(3);

    if (hue < 60)
        data = {c, x, 0.f};
    else if (hue < 120)
        data = {x, c, 0.f};
    else if (hue < 180)
        data = {0.f, c, x};
    else if (hue < 240)
        data = {0.f, x, c};
    else if (hue < 300)
        data = {x, 0.f, c};
    else
        data = {c, 0.f, x};

    auto m = value - c;

    return util::Color(data[0] + m,
                       data[1] + m,
                       data[2] + m);
}

std::string util::Color::AsHex3String() const
{
    return util::Format("#%06x", this->data & ~A_MASK);
}

std::string util::Color::AsHex4String() const
{
    return util::Format("#%06x%02x", this->data & ~A_MASK, this->data >> A_SHIFT);
}

util::Color util::Color::FromHexString(const std::string &value)
{
    if (value.length() == 4) //#rgb
    {
        return Color(util::HexToNumber(value[1]) / 15.f,
                     util::HexToNumber(value[2]) / 15.f,
                     util::HexToNumber(value[3]) / 15.f);
    }
    else if (value.length() == 5) //#rgba
    {
        return Color(util::HexToNumber(value[1]) / 15.f,
                     util::HexToNumber(value[2]) / 15.f,
                     util::HexToNumber(value[3]) / 15.f,
                     util::HexToNumber(value[4]) / 15.f);
    }
    else if (value.length() == 7) //#rrggbb
    {
        return Color(A_MASK | util::HexToNumber(value.c_str() + 1));
    }
    else if (value.length() == 9) //#rrggbbaa
    {
        auto all = util::HexToNumber(value.c_str() + 1);

        return Color((all >> 8) | (all << 24));
    }
}