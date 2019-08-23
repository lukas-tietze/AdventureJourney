#pragma once

#include "controls/containers/ContainerBase.hpp"

namespace terminal
{
class PlacementBox : public ContainerBase
{
  private:
    ControlBase *item;
    
    float top;
    float bottom;
    float left;
    float right;
    float width;
    float height;

  public:
    PlacementBox();

    void Add(ControlBase *);
    bool Remove(ControlBase *);

    void RestoreLayout();
    void SetTop(float);
    void SetBottom(float);
    void SetLeft(float);
    void SetRight(float);
    void SetItemWidth(float);
    void SetItemHeight(float);

    void SetHorizontalPartition(float, float, float);
    void SetVerticalPartition(float, float, float);
};
} // namespace terminal
