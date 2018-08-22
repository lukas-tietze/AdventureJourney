#ifndef POINT_HPP
#define POINT_HPP

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

    basic_point<T> operator+(const basic_point<T> &other)
    {
        return basic_point(this->x + other.x, this->y + other.y);
    }

    basic_point<T> operator-(const basic_point<T> &other)
    {
        return basic_point(this->x + other.x, this->y + other.y);
    }

    basic_point<T> operator*(const double &fac)
    {
        return basic_point(this->x * fac, this->y * fac);
    }

    basic_point<T> operator/(const double &fac)
    {
        return basic_point((int)this->x * fac, this->y * fac);
    }

    bool operator==(const basic_point<T> &other)
    {
        return this->x == other.x && this->y == other.y;
    }

    bool operator!=(const basic_point<T> &other)
    {
        return this->x != other.x || this->y != other.y;
    }
}; /*basic_point*/

typedef basic_point<int> point;
typedef basic_point<float> pointf;
} // namespace util

#endif /*POINT_HPP*/