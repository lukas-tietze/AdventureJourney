#pragma once

#include "data/math.hpp"

#include <iostream>

namespace util
{
template <class T>
class BasicDimension
{
  private:
    T width;
    T height;

  public:
    BasicDimension(const util::BasicDimension<T> &copy) : width(copy.width),
                                                            height(copy.height)
    {
    }

    BasicDimension(T width, T height) : width(width),
                                         height(height)
    {
    }

    BasicDimension() : width(0),
                        height(0)
    {
    }

    T GetWidth() const
    {
        return this->width;
    }

    T GetHeight() const
    {
        return this->height;
    }

    T GetArea() const
    {
        return this->width * this->height;
    }

    util::BasicDimension<T> Crop(const util::BasicDimension<T> &min, const util::BasicDimension<T> &max) const
    {
        return util::BasicDimension<T>(
            util::Crop(this->width, min.width, max.width),
            util::Crop(this->height, min.height, max.height));
    }

    bool operator==(const util::BasicDimension<T> &other) const
    {
        return this->width == other.width && this->height == other.height;
    }

    bool operator!=(const util::BasicDimension<T> &other) const
    {
        return this->width != other.width || this->height != other.height;
    }

    template <class Tx>
    friend BasicDimension<Tx> operator*(const double &, const BasicDimension<Tx> &);

    template <class Tx>
    friend BasicDimension<Tx> operator*(const BasicDimension<Tx> &, const double &);

    template <class Tx>
    friend BasicDimension<Tx> operator/(const BasicDimension<Tx> &, const double &);

    template <class Tx>
    friend std::ostream &operator<<(std::ostream &, const util::BasicDimension<Tx> &);
}; /*BasicDimension*/

template <class T>
util::BasicDimension<T> operator*(const double &f, const BasicDimension<T> &d)
{
    return BasicDimension<T>(f * d.width, f * d.height);
}

template <class T>
util::BasicDimension<T> operator*(const BasicDimension<T> &d, const double &f)
{
    return BasicDimension<T>(d.width * f, d.height * f);
}

template <class T>
util::BasicDimension<T> operator/(const BasicDimension<T> &d, const double &f)
{
    return BasicDimension<T>(d.width / f, d.height / f);
}

template <class T>
std::ostream &operator<<(std::ostream &s, const util::BasicDimension<T> &d)
{
    s << '(' << d.width << 'x' << d.height << ')';

    return s;
}

typedef BasicDimension<int> Dimension;
typedef BasicDimension<float> DimensionF;
} // namespace util