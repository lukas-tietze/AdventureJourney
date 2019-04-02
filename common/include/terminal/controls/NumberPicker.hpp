#pragma once

#include "terminal/controls/ControlBase.hpp"

namespace terminal
{
class NumberPicker : public ControlBase
{
  private:
    int min;
    int max;
    int step;
};
} // namespace terminal
