#pragma once

#include "terminal/controls/containers/ContainerBase.hpp"

namespace terminal
{
class ScrollContainer : public ContainerBase
{
  private:
    bool scrollVertical;
    bool scrollHorizontal;

  public:
    ScrollContainer();
};
} // namespace terminal