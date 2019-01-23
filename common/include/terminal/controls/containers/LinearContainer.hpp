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
    virtual void Add(Orientation where, ControlBase *item);
    virtual void RestoreLayout();

  private:
    Orientation orientation;
};
} // namespace terminal