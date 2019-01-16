#pragma once

<<<<<<< HEAD
#include "terminal/controls/ControlBase.hpp"
=======
#include "terminal/controls/containers/ContainerBase.hpp"
>>>>>>> 2eb1c4acdb40749a0ddd5eeb429b7b2e1c376271

namespace terminal
{
class LinearContainer : public ContainerBase
{
  public:
    LinearContainer();
<<<<<<< HEAD
    virtual ~LinearContainer();

    enum class Orientation
    {
        Horizontal,
        Vertical,
    };

    virtual void Add(ControlBase *item);

  private:
    Orientation orientation;
=======
>>>>>>> 2eb1c4acdb40749a0ddd5eeb429b7b2e1c376271
};
} // namespace terminal