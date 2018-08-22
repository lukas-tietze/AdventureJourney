#ifndef DIMENSION_HPP
#define DIMENSION_HPP

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
}; /*basic_dimension*/

typedef basic_dimension<int> dimension;
typedef basic_dimension<float> dimensionf;
} // namespace util

#endif /*DIMENSION_HPP*/