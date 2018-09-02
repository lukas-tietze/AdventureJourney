#pragma once

#include <iostream>

namespace util
{
template <class T>
class basic_dimension
{
  private:
    T width;
    T height;

  public:
    basic_dimension(const util::basic_dimension<T> &copy) : width(copy.width),
                                                            height(copy.height)
    {
    }

    basic_dimension(T width, T height) : width(width),
                                         height(height)
    {
    }

    basic_dimension() : width(0),
                        height(0)
    {
    }

    T get_width() const
    {
        return this->width;
    }

    T get_height() const
    {
        return this->height;
    }

    T get_area() const
    {
        return this->width * this->height;
    }

    
    template <class Tx>
    friend basic_dimension<Tx> operator*(const double &, const basic_dimension<Tx> &);
    
    template <class Tx>
    friend basic_dimension<Tx> operator*(const basic_dimension<Tx> &, const double &);
    
    template <class Tx>
    friend basic_dimension<Tx> operator/(const basic_dimension<Tx> &, const double &);
    
    template <class Tx>
    friend std::ostream &operator<<(std::ostream &, const util::basic_dimension<Tx> &);
}; /*basic_dimension*/

template <class T>
util::basic_dimension<T> operator*(const double &f, const basic_dimension<T> &d)
{
    return basic_dimension<T>(f * d.width, f * d.height);
}

template <class T>
util::basic_dimension<T> operator*(const basic_dimension<T> &d, const double &f)
{
    return basic_dimension<T>(d.width * f, d.height * f);
}

template <class T>
util::basic_dimension<T> operator/(const basic_dimension<T> &d, const double &f)
{
    return basic_dimension<T>(d.width / f, d.height / f);
}

template <class T>
std::ostream &operator<<(std::ostream &s, const util::basic_dimension<T> &d)
{
    s << '(' << d.width << 'x' << d.height << ')';

    return s;
}

typedef basic_dimension<int> dimension;
typedef basic_dimension<float> dimensionf;
} // namespace util