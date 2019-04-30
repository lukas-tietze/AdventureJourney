#include "terminal/controls/Checkbox.hpp"

terminal::Checkbox::Checkbox() : ControlBase()
{
}

bool terminal::Checkbox::IsChecked() const
{
    return this->state == CheckState::Checked;
}

void terminal::Checkbox::SetChecked(bool checked)
{
    this->state = checked ? CheckState::Checked : CheckState::Unchecked;
}

terminal::CheckState terminal::Checkbox::GetCheckState() const
{
    return this->state;
}

void terminal::Checkbox::SetCheckState(CheckState state)
{
    this->state = state;
}

void terminal::Checkbox::SetThreewayModeEnabled(bool enabled)
{
    this->threeway_mode = enabled;
}

bool terminal::Checkbox::IsThreeewayModeEnabled() const
{
    return this->threeway_mode;
}

void terminal::Checkbox::HandleKey(KeyInput &input)
{
    if (input.key == ' ')
        this->SwitchCheckState();
}

void terminal::Checkbox::HandleMouse(MouseInput &input)
{
    if (input.action == MouseAction::Button1Clicked)
        this->SwitchCheckState();
}

void terminal::Checkbox::Render(Canvas &c)
{
    auto bounds = this->GetBounds();
    auto line = (bounds.GetMaxY() + bounds.GetMinY()) / 2;

    c.DrawBox(this->GetBounds(), '-', '|', '+');

    switch (this->state)
    {
    case CheckState::Checked:
        c.DrawString(util::Point(bounds.GetMinX(), line), "|X|");
        break;
    case CheckState::Midway:
        c.DrawString(util::Point(bounds.GetMinX(), line), "|O|");
        break;
    case CheckState::Unchecked:
        c.DrawString(util::Point(bounds.GetMinX(), line), "| |");
        break;
    }
}

void terminal::Checkbox::SwitchCheckState()
{
    if (this->threeway_mode)
    {
        switch (this->state)
        {
        case CheckState::Checked:
        case CheckState::Midway:
            this->SetCheckState(CheckState::Unchecked);
            break;
        case CheckState::Unchecked:
            this->SetCheckState(CheckState::Checked);
            break;
        }
    }
    else
    {
        this->SetChecked(!this->IsChecked());
    }
}
