#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <cmath>
#include <algorithm>

#include "dimension.hpp"
#include "point.hpp"

namespace util
{
template <class T>
class basic_rectangle
{
  private:
    basic_point<T> location;
    basic_dimension<T> size;

  public:
    basic_rectangle(const util::basic_rectangle<T> &copy) : location(copy.location),
                                                            size(copy.size)
    {
    }

    basic_rectangle(const util::basic_point<T> &location, const util::basic_dimension<T> &size) : location(location),
                                                                                                  size(size)
    {
    }

    basic_rectangle(const util::basic_point<T> &location, T width, T height) : location(location),
                                                                               size(width, height)
    {
    }

    basic_rectangle(T x, T y, const util::basic_dimension<T> &size) : location(x, y),
                                                                      size(size)
    {
    }

    basic_rectangle(T x, T y, T width, T height) : location(x, y),
                                                   size(width, height)
    {
    }

    T get_x() const
    {
        return this->location.get_x();
    }

    T get_y() const
    {
        return this->location.get_y();
    }

    T get_min_x() const
    {
        return this->location.get_x();
    }

    T get_max_x() const
    {
        return this->location.get_x() + this->size.get_width();
    }

    T get_min_y() const
    {
        return this->location.get_y();
    }

    T get_max_y() const
    {
        return this->location.get_y() + this->size.get_height();
    }

    T get_width() const
    {
        return this->size.get_width();
    }

    T get_height() const
    {
        return this->size.get_height();
    }

    T get_area() const
    {
        return this->dimension.get_area();
    }

    const util::basic_point<T> &get_location() const
    {
        return this->location;
    }

    const util::basic_dimension<T> &get_size() const
    {
        return this->size;
    }

    util::basic_rectangle<T> resize(double factor) const
    {
        return basic_rectangle<T>(this->location, this->dimension * factor);
    }

    util::basic_rectangle<T> resize(const util::basic_dimension<T> &d) const
    {
        return basic_rectangle<T>(this->location, d);
    }

    util::basic_rectangle<T> relocate(const util::basic_point<T> &p) const
    {
        return basic_rectangle<T>(p, this->dimension);
    }

    basic_point<T> fit(const util::basic_point<T> &p)
    {
        return basic_point<T>(util::crop(p.get_x(), this->get_min_x(), this->get_max_x()),
                              util::crop(p.get_y(), this->get_min_y(), this->get_max_y()));
    }

    util::basic_rectangle<T> intersect(const basic_rectangle<T> &other) const
    {
        T xa1 = this->location.get_x();
        T xa2 = this->location.get_x() + this->size.get_width();
        T ya1 = this->location.get_y();
        T ya2 = this->location.get_y() + this->size.get_height();

        T xb1 = other.location.get_x();
        T xb2 = other.location.get_x() + other.size.get_width();
        T yb1 = other.location.get_y();
        T yb2 = other.location.get_y() + other.size.get_height();

        T xi1 = std::max(xa1, xb1);
        T xi2 = std::min(xa2, xb2);
        T yi1 = std::min(ya1, yb1);
        T yi2 = std::max(ya2, yb2);

        return basic_rectangle(xi1, yi1, xi2 - xi1, yi2 - yi1);
    }
}; /*basic_rectangle*/

typedef basic_rectangle<int> rectangle;
typedef basic_rectangle<float> rectanglef;
} // namespace util

#endif /*RECTANGLE_HPP*/