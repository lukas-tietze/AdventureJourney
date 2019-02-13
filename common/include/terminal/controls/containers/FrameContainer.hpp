#pragma once

#include <tuple>
#include <vector>

#include "terminal/controls/containers/ContainerBase.hpp"

namespace terminal
{
class FrameContainer : public ContainerBase
{
  private:
    ControlBase *controls[5];
    int weights[5];
    bool weightsFixed[5];
    int minWidths[4];
    int maxWidths[4];

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
} // namespace terminal