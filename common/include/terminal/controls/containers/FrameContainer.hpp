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
    int weigths[5];
    bool weigthsFixed[5];

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
    void SetWeigth(Orientation, int);

    void Render(Canvas &);
};
} // namespace terminal