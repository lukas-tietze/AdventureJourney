#pragma once

#include "controls/ControlBase.hpp"

namespace terminal
{
class ContainerBase : public ControlBase
{
  private:
    std::vector<terminal::ControlBase *> controls;
    int focusedControlIndex;

    void SwitchFocus(int);

  protected:
    std::vector<terminal::ControlBase *> &GetControls();
    const std::vector<terminal::ControlBase *> &GetControls() const;

  public:
    ContainerBase();
    virtual ~ContainerBase();

    virtual void Add(ControlBase *item);
    virtual bool Remove(ControlBase *item);

    virtual void HandleChildZIndexChanged(ControlBase *);
    virtual void HandleChildTabIndexChanged(ControlBase *);

    virtual void HandleFocusAquired();
    virtual void HandleFocusLost();
    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);
    virtual void HandleZIndexChanged(int);
    virtual void HandleTabIndexChanged(int);

    virtual void Render(Canvas &);

    ControlBase *GetFocusedControl();
    const ControlBase *GetFocusedControl() const;
    size_t GetFocusedControlIndex() const;
    bool RequestFocus(ControlBase *);

    virtual void RestoreLayout();
};
} // namespace terminal