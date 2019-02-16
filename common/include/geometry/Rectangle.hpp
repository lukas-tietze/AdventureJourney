#pragma once

#include <cmath>
#include <algorithm>

#include "Dimension.hpp"
#include "Point.hpp"

namespace util
{
template <class T>
class BasicRectangle
{
  private:
    BasicPoint<T> location;
    BasicDimension<T> size;

  public:
    BasicRectangle() : location(),
                       size()
    {
    }

    BasicRectangle(const util::BasicRectangle<T> &copy) : location(copy.location),
                                                          size(copy.size)
    {
    }

    BasicRectangle(const util::BasicPoint<T> &location, const util::BasicDimension<T> &size) : location(location),
                                                                                               size(size)
    {
    }

    BasicRectangle(const util::BasicPoint<T> &location, T width, T height) : location(location),
                                                                             size(width, height)
    {
    }

    BasicRectangle(T x, T y, const util::BasicDimension<T> &size) : location(x, y),
                                                                    size(size)
    {
    }

    BasicRectangle(T x, T y, T width, T height) : location(x, y),
                                                  size(width, height)
    {
    }

    void SetX(T value)
    {
        this->location.SetX(value);
    }

    void SetY(T value)
    {
        this->location.SetY(value);
    }

    void SetWidth(T value)
    {
        this->size.SetWidth(value);
    }

    void SetHeight(T value)
    {
        this->size.SetHeight(value);
    }

    void SetLocation(const BasicPoint<T> &value)
    {
        this->location = value;
    }

    void SetSize(const BasicDimension<T> &value)
    {
        this->size = value;
    }

    T GetX() const
    {
        return this->location.GetX();
    }

    T GetY() const
    {
        return this->location.GetY();
    }

    T GetMinX() const
    {
        return this->location.GetX();
    }

    T GetMaxX() const
    {
        return this->location.GetX() + this->size.GetWidth();
    }

    T GetMinY() const
    {
        return this->location.GetY();
    }

    T GetMaxY() const
    {
        return this->location.GetY() + this->size.GetHeight();
    }

    T GetWidth() const
    {
        return this->size.GetWidth();
    }

    T GetHeight() const
    {
        return this->size.GetHeight();
    }

    T GetArea() const
    {
        return this->size.GetArea();
    }

    BasicRectangle<T> GetLeftSub(T units) const
    {
        return BasicRectangle<T>(this->GetLocation(),
                                 units,
                                 this->GetHeight());
    }

    BasicRectangle<T> &MoveLeftEdge(T units)
    {
        this->location.SetX(this->GetX() + units);
        this->size.SetWidth(this->GetWidth() - units);

        return *this;
    }

    BasicRectangle<T> MoveLeftEdge(T units) const
    {
        return BasicRectangle<T>(this->location.GetX() + units,
                                 this->location.GetY(),
                                 this->size.GetWidth() - units,
                                 this->size.GetHeight());
    }

    BasicRectangle<T> GetRightSub(T units) const
    {
        return BasicRectangle<T>(this->GetMaxX() - units,
                                 this->GetMinY(),
                                 units,
                                 this->GetHeight());
    }

    BasicRectangle<T> &MoveRightEdge(T units)
    {
        this->size.SetWidth(this->GetWidth() + units);

        return *this;
    }

    BasicRectangle<T> MoveRightEdge(T units) const
    {
        return util::BasicRectangle<T>(this->location,
                                       this->size.GetWidth() + units,
                                       this->size.GetHeight());
    }

    BasicRectangle<T> GetTopSub(T units) const
    {
        return BasicRectangle<T>(this->GetLocation(),
                                 this->GetWidth(),
                                 units);
    }

    BasicRectangle<T> &MoveTopEdge(T units)
    {
        this->location.SetY(this->GetY() + units);
        this->size.SetHeight(this->GetHeight() - units);

        return *this;
    }

    BasicRectangle<T> MoveTopEdge(T units) const
    {
        return BasicRectangle<T>(this->location.GetX(),
                                 this->location.GetY() + units,
                                 this->size.GetWidth(),
                                 this->size.GetHeight() - units);
    }

    BasicRectangle<T> GetBottomSub(T units) const
    {
        return BasicRectangle<T>(this->GetMinX(),
                                 this->GetMaxY() - units,
                                 this->GetWidth(),
                                 units);
    }

    BasicRectangle<T> &MoveBottomEdge(T units)
    {
        this->size.SetHeight(this->GetHeight() + units);

        return *this;
    }

    BasicRectangle<T> MoveBottomEdge(T units) const
    {
        return BasicRectangle<T>(this->location,
                                 this->size.GetWidth(),
                                 this->size.GetHeight() + units);
    }

    const util::BasicPoint<T> &GetLocation() const
    {
        return this->location;
    }

    const util::BasicDimension<T> &GetSize() const
    {
        return this->size;
    }

    util::BasicRectangle<T> Resize(double factor) const
    {
        return BasicRectangle<T>(this->location, this->dimension * factor);
    }

    util::BasicRectangle<T> Resize(const util::BasicDimension<T> &d) const
    {
        return BasicRectangle<T>(this->location, d);
    }

    util::BasicRectangle<T> Relocate(const util::BasicPoint<T> &p) const
    {
        return BasicRectangle<T>(p, this->dimension);
    }

    bool Contains(const util::BasicPoint<T> &p) const
    {
        return this->GetMinX() <= p.GetX() &&
               this->GetMaxX() >= p.GetX() &&
               this->GetMinY() <= p.GetY() &&
               this->GetMaxY() >= p.GetY();
    }

    BasicPoint<T> Fit(const util::BasicPoint<T> &p) const
    {
        return BasicPoint<T>(util::Crop(p.GetX(), this->GetMinX(), this->GetMaxX()),
                             util::Crop(p.GetY(), this->GetMinY(), this->GetMaxY()));
    }

    bool HasIntersection(const BasicRectangle<T> &other) const
    {
        return this->GetMinX() < other.GetMaxX() &&
               this->GetMaxX() > other.GetMinX() &&
               this->GetMinY() < other.GetMaxY() &&
               this->GetMaxY() > other.GetMinY();
    }

    util::BasicRectangle<T> Intersect(const BasicRectangle<T> &other) const
    {
        if (!this->HasIntersection(other))
            return BasicRectangle(0, 0, 0, 0);

        T xi1 = std::max<T>(this->GetMinX(), other.GetMinX());
        T xi2 = std::min<T>(this->GetMaxX(), other.GetMaxX());
        T yi1 = std::max<T>(this->GetMinY(), other.GetMinY());
        T yi2 = std::min<T>(this->GetMaxY(), other.GetMaxY());

        return BasicRectangle<T>(xi1, yi1, xi2 - xi1, yi2 - yi1);
    }

    bool operator==(const util::BasicRectangle<T> &other) const
    {
        return other.location == this->location && other.size == this->size;
    }

    bool operator!=(const util::BasicRectangle<T> &other) const
    {
        return other.location != this->location || other.size != this->size;
    }

    template <class Tx>
    friend std::ostream &operator<<(std::ostream &, const util::BasicRectangle<Tx> &);
}; /*BasicRectangle*/

template <class T>
std::ostream &operator<<(std::ostream &s, const util::BasicRectangle<T> &r)
{
    s << "(" << r.GetMinX() << ", " << r.GetMinY() << ") -> (" << r.GetWidth() << "X" << r.GetHeight() << ")";

    return s;
}

typedef BasicRectangle<int> Rectangle;
typedef BasicRectangle<float> RectangleF;
} // namespace util