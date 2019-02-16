#pragma once

#include <tuple>
#include <vector>
#include <ostream>

#include "terminal/controls/containers/ContainerBase.hpp"

namespace terminal
{
class FrameContainer : public ContainerBase
{
  private:
    ControlBase *controls[5];
    int weights[5];
    bool weightsFixed[5];
    int minSizes[4];
    int maxSizes[4];

  public:
    FrameContainer();
    virtual ~FrameContainer();

    enum class Orientation
    {
        Left,
        Right,
        Top,
        Bottom,
        Center,
    };

    void Add(ControlBase *);
    void Add(Orientation, ControlBase *);
    bool Remove(ControlBase *);

    void RestoreLayout();
    void SetWeight(Orientation, int);
    void SetMaxSize(Orientation, int);
    void SetMinSize(Orientation, int);

    void Render(Canvas &);
};

std::ostream &operator<<(std::ostream &s, terminal::FrameContainer::Orientation value);
} // namespace terminal