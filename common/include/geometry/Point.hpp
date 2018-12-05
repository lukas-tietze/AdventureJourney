#pragma once

#include "data/Math.hpp"

namespace util
{
template <class T>
class BasicPoint
{
  private:
    T x;
    T y;

  public:
    BasicPoint(const BasicPoint<T> &copy) : x(copy.x),
                                              y(copy.y)
    {
    }

    BasicPoint(T x, T y) : x(x),
                            y(y)
    {
    }

    BasicPoint() : x(0),
                    y(0)
    {
    }

    T GetX() const
    {
        return this->x;
    }

    T GetY() const
    {
        return this->y;
    }

    util::BasicPoint<T> Crop(const util::BasicPoint<T> &min, const util::BasicPoint<T> &max) const
    {
        return util::BasicPoint<T>(
            util::crop(this->x, min.x, max.x),
            util::crop(this->y, min.y, max.y));
    }

    bool operator==(const util::BasicPoint<T> &other) const
    {
        return this->x == other.x && this->y == other.y;
    }

    bool operator!=(const util::BasicPoint<T> &other) const
    {
        return this->x != other.x || this->y != other.y;
    }

    template <class Tx>
    friend BasicPoint<Tx> operator+(const BasicPoint<Tx> &, const BasicPoint<Tx> &);

    template <class Tx>
    friend BasicPoint<Tx> operator-(const BasicPoint<Tx> &, const BasicPoint<Tx> &);

    template <class Tx>
    friend BasicPoint<Tx> operator*(const BasicPoint<Tx> &, const double &);

    template <class Tx>
    friend BasicPoint<Tx> operator/(const BasicPoint<Tx> &, const double &);

    template <class Tx>
    friend BasicPoint<Tx> operator*(const double &, const BasicPoint<Tx> &);

    template <class Tx>
    friend std::ostream &operator<<(std::ostream &, const BasicPoint<Tx> &);
};

template <class T>
BasicPoint<T> operator+(const BasicPoint<T> &p, const BasicPoint<T> &f)
{
    return BasicPoint<T>(p.x + f.x, p.y + f.y);
}

template <class T>
BasicPoint<T> operator-(const BasicPoint<T> &p, const BasicPoint<T> &f)
{
    return BasicPoint<T>(p.x - f.x, p.y - f.y);
}

template <class T>
BasicPoint<T> operator*(const BasicPoint<T> &p, const double &f)
{
    return BasicPoint<T>(p.x * f, p.y * f);
}

template <class T>
BasicPoint<T> operator/(const BasicPoint<T> &p, const double &f)
{
    return BasicPoint<T>(p.x / f, p.y / f);
}

template <class T>
BasicPoint<T> operator*(const double &f, const BasicPoint<T> &p)
{
    return BasicPoint<T>(f * p.x, f * p.x);
}

template <class T>
std::ostream &operator<<(std::ostream &s, const BasicPoint<T> &p)
{
    s << '(' << p.x << ", " << p.y << ')';

    return s;
}

typedef BasicPoint<int> Point;
typedef BasicPoint<float> PointF;
} // namespace util