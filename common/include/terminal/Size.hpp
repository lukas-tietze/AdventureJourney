#pragma once

#include "terminal/controls/ControlBase.hpp"

namespace terminal
{
class Size
{
  public:
    Size();
    Size(float f);
    Size(int i);

    int operator[](int);

  private:
    float rel;
};
} // namespace terminal
