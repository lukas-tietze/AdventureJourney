#pragma once

#include "geometry/Dimension.hpp"

namespace terminal
{
class ControlBase;

class Dimension
{
  private:
    struct Dim
    {
        bool isRelative;
        union value {
            float relative;
            int absolute;
        };
    };

    Dim width;
    Dim height;

  public:
    util::Dimension operator[](const terminal::ControlBase *) const;
};
} // namespace terminal