#pragma once

#include <cmath>
#include <algorithm>

#include "Dimension.hpp"
#include "Point.hpp"

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
        return this->size.get_area();
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

    bool contains(const util::basic_point<T> &p) const
    {
        return this->get_min_x() <= p.get_x() &&
               this->get_max_x() >= p.get_x() &&
               this->get_min_y() <= p.get_y() &&
               this->get_max_x() >= p.get_y();
    }

    basic_point<T> fit(const util::basic_point<T> &p) const
    {
        return basic_point<T>(util::crop(p.get_x(), this->get_min_x(), this->get_max_x()),
                              util::crop(p.get_y(), this->get_min_y(), this->get_max_y()));
    }

    bool has_intersection(const basic_rectangle<T> &other) const
    {
        return this->get_min_x() < other.get_max_x() &&
               this->get_max_x() > other.get_min_x() &&
               this->get_min_y() < other.get_max_y() &&
               this->get_max_y() > other.get_min_y();
    }

    util::basic_rectangle<T> intersect(const basic_rectangle<T> &other) const
    {
        if (!this->has_intersection(other))
            return basic_rectangle(0, 0, 0, 0);

        T xi1 = std::max<T>(this->get_min_x(), other.get_min_x());
        T xi2 = std::min<T>(this->get_max_x(), other.get_max_x());
        T yi1 = std::max<T>(this->get_min_y(), other.get_min_y());
        T yi2 = std::min<T>(this->get_max_y(), other.get_max_y());

        return basic_rectangle<T>(xi1, yi1, xi2 - xi1, yi2 - yi1);
    }

    bool operator==(const util::basic_rectangle<T> &other) const
    {
        return other.location == this->location && other.size == this->size;
    }

    bool operator!=(const util::basic_rectangle<T> &other) const
    {
        return other.location != this->location || other.size != this->size;
    }

    template <class Tx>
    friend std::ostream &operator<<(std::ostream &, const util::basic_rectangle<Tx> &);
}; /*basic_rectangle*/

template <class T>
std::ostream &operator<<(std::ostream &s, const util::basic_rectangle<T> &r)
{
    s << "(" << r.get_min_x() << ", " << r.get_min_y() << ") -> (" << r.get_width() << "X" << r.get_height() << ")";

    return s;
}

typedef basic_rectangle<int> Rectangle;
typedef basic_rectangle<float> RectangleF;
} // namespace util