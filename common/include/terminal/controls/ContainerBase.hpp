#pragma once

#include "terminal/controls/ControlBase.hpp"

namespace terminal
{
class ContainerBase : public ControlBase
{
  public:
    ContainerBase();
    virtual ~ContainerBase();

    virtual void HandleChildZIndexChanged(ControlBase *);
    virtual void HandleChildTabIndexChanged(ControlBase *);
    
    virtual void HandleFocusAquired();
    virtual void HandleFocusLost();
    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);
    virtual void HandleAddToControl(ContainerBase *);
    virtual void HandleZIndexChanged(int);
    virtual void HandleTabIndexChanged(int);

    virtual void Render(Canvas &);
};
} // namespace terminal