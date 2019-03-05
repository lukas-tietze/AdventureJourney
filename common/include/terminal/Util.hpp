#pragma once

#include "geometry/Dimension.hpp"

namespace terminal
{
class Dimension
{
  private:
    struct Dim
    {
        union Value {
            float relative;
            int absolute;
        };

        bool isRelative;
        Value value;
    };

    Dim width;
    Dim height;

  public:
    Dimension(int, int);
    Dimension(int, float);
    Dimension(float, float);
    Dimension(float, int);

    util::Dimension Convert(const util::Dimension &d) const;

    int Width(const util::Dimension &) const;
    int Height(const util::Dimension &) const;

    void SetWidth(int);
    void SetWidth(float);

    void SetHeight(int);
    void SetHeight(float);
};
} // namespace terminal