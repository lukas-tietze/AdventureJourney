#pragma once

#include "ControlBase.hpp"
#include "Event.hpp"

namespace terminal
{
enum class CheckState
{
    Checked,
    Midway,
    Unchecked,
};

class Checkbox : public terminal::ControlBase
{
  private:
    CheckState state;
    bool threeway_mode;

    void SwitchCheckState();

  public:
    Checkbox();

    bool IsChecked() const;
    void SetChecked(bool checked);
    CheckState GetCheckState() const;
    void SetCheckState(CheckState);
    void SetThreewayModeEnabled(bool);
    bool IsThreeewayModeEnabled() const;

    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);

    virtual void Render(Canvas &);
};
} // namespace terminal