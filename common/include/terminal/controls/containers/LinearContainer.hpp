#pragma once

#include "terminal/controls/containers/ContainerBase.hpp"

namespace terminal
{
class LinearContainer : public ContainerBase
{
  public:
    LinearContainer();
    virtual ~LinearContainer();

    enum class Orientation
    {
        Horizontal,
        Vertical,
    };

    virtual void Add(ControlBase *item);

  private:
    Orientation orientation;
};
} // namespace terminal