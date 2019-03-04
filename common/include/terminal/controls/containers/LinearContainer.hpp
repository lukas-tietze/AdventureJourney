#pragma once

#include "terminal/controls/containers/ContainerBase.hpp"

namespace terminal
{
class LinearContainer : public ContainerBase
{
  public:
    enum class Orientation
    {
        LeftToRight,
        RightToLeft,
        BottomToTop,
        TopToBottom,
    };
    
    LinearContainer();
    virtual ~LinearContainer();

    virtual void Add(ControlBase *item);
    virtual bool Remove(ControlBase *item);
    virtual void RestoreLayout();

    void SetOrientation(Orientation);

  private:
    Orientation orientation;
};
} // namespace terminal