#pragma once

#include <tuple>
#include <vector>

#include "terminal/controls/containers/ContainerBase.hpp"

namespace terminal
{
class FrameContainer : public ContainerBase
{
  private:
    ControlBase *top;
    ControlBase *bottom;
    ControlBase *left;
    ControlBase *right;
    ControlBase *center;

  public:
    FrameContainer();

    enum class Orientation
    {
        Left,
        Right,
        Top,
        Bottom,
        Center,
    };

    virtual void Add(ControlBase *item);
    virtual void Add(Orientation where, ControlBase *item);
    virtual void RestoreLayout();
};
} // namespace terminal