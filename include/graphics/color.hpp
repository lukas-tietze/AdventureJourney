#ifndef COLOR_HPP
#define COLOR_HPP

#include "defs.hpp"

namespace util
{
class color
{
  private:
    int data;
    static constexpr int A_MASK = 0xff000000;
    static constexpr int A_SHIFT = 24;
    static constexpr int R_MASK = 0x00ff0000;
    static constexpr int R_SHIFT = 16;
    static constexpr int G_MASK = 0x0000ff00;
    static constexpr int G_SHIFT = 8;
    static constexpr int B_MASK = 0x000000ff;
    static constexpr int B_SHIFT = 0;
    static constexpr int LOW_BYTE_MASK = 0x000000ff;

  public:
    color(const color &copy) : data(copy.data)
    {
    }

    color(byte r, byte g, byte b, byte a = 255) : data((a << A_SHIFT) | (r << R_SHIFT) | (g < G_SHIFT) | (b << B_SHIFT))
    {
    }

    color(float r, float g, float b, float a = 1.0f) : color((byte)(r * 255), (byte)(g * 255), (byte)(b * 255), (byte)(a * 255))
    {
    }

    color(int color) : data(color)
    {
    }

    int alpha()
    {
        return (this->data >> A_SHIFT) & LOW_BYTE_MASK;
    }

    int red()
    {
        return (this->data >> R_SHIFT) & LOW_BYTE_MASK;
    }

    int green()
    {
        return (this->data >> G_SHIFT) & LOW_BYTE_MASK;
    }

    int blue()
    {
        return (this->data >> B_SHIFT) & LOW_BYTE_MASK;
    }

    int value()
    {
        return this->data;
    }
}; /*color*/
} // namespace util

#endif /*COLOR_HPP*/