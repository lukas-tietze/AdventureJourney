#ifndef POINT_HPP
#define POINT_HPP

#include "data/math.hpp"

namespace util
{
template <class T>
class basic_point
{
  private:
    T x;
    T y;

  public:
    basic_point(const basic_point<T> &copy) : x(copy.x),
                                              y(copy.y)
    {
    }

    basic_point(T x, T y) : x(x),
                            y(y)
    {
    }

    basic_point() : x(0),
                    y(0)
    {
    }

    T get_x() const
    {
        return this->x;
    }

    T get_y() const
    {
        return this->y;
    }

    template <class Tx>
    friend basic_point<Tx> operator+(const basic_point<Tx> &, const basic_point<Tx> &);
    template <class Tx>
    friend basic_point<Tx> operator-(const basic_point<Tx> &, const basic_point<Tx> &);
    template <class Tx>
    friend basic_point<Tx> operator*(const basic_point<Tx> &, const double &);
    template <class Tx>
    friend basic_point<Tx> operator/(const basic_point<Tx> &, const double &);
    template <class Tx>
    friend basic_point<Tx> operator*(const double &, const basic_point<Tx> &);
    template <class Tx>
    friend std::ostream &operator<<(std::ostream &, const basic_point<Tx> &);
};
template <class T>
basic_point<T> operator+(const basic_point<T> &p, const basic_point<T> &f)
{
    return basic_point<T>(p.x + f.x, p.y + f.y);
}

template <class T>
basic_point<T> operator-(const basic_point<T> &p, const basic_point<T> &f)
{
    return basic_point<T>(p.x - f.x, p.y - f.y);
}

template <class T>
basic_point<T> operator*(const basic_point<T> &p, const double &f)
{
    return basic_point<T>(p.x * f, p.y * f);
}

template <class T>
basic_point<T> operator/(const basic_point<T> &p, const double &f)
{
    return basic_point<T>(p.x / f, p.y / f);
}

template <class T>
basic_point<T> operator*(const double &f, const basic_point<T> &p)
{
    return basic_point<T>(f * p.x, f * p.x);
}

template <class T>
std::ostream &operator<<(std::ostream &s, const basic_point<T> &p)
{
    s << '(' << p.x << ", " << p.y << ')';

    return s;
}

typedef basic_point<int> point;
typedef basic_point<float> pointf;
} // namespace util

#endif /*POINT_HPP*/