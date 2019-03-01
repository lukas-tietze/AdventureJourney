#pragma once

#include "terminal/controls/containers/ContainerBase.hpp"

namespace terminal
{
class PlacementBox : public ContainerBase
{
  private:
    ControlBase *item;
    float weights[4];

  public:
    PlacementBox();
    virtual ~PlacementBox();

    void Add(ControlBase *);
    bool Remove(ControlBase *);

    void RestoreLayout();
    void SetTop(float);
    void SetBottom(float);
    void SetLeft(float);
    void SetRight(float);
};
} // namespace terminal
