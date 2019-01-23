#include "terminal/controls/containers/ContainerBase.hpp"
#include "geometry/Rectangle.hpp"

terminal::ContainerBase::ContainerBase() : ControlBase()
{
    this->SwitchFocus(-1);
}

terminal::ContainerBase::~ContainerBase()
{
    while (!this->controls.empty())
    {
        delete this->controls.back();
        this->controls.pop_back();
    }
}

void terminal::ContainerBase::HandleChildZIndexChanged(ControlBase *)
{
}

void terminal::ContainerBase::HandleChildTabIndexChanged(ControlBase *)
{
}

void terminal::ContainerBase::HandleFocusAquired()
{
}

void terminal::ContainerBase::HandleFocusLost()
{
}

void terminal::ContainerBase::HandleKey(KeyInput &input)
{
    this->ControlBase::HandleKey(input);

    if (input.handled)
        return;

    if (this->focusedControlIndex >= 0)
        this->controls[focusedControlIndex]->HandleKey(input);

    if (input.handled)
        return;

    if (!this->controls.empty() && input.key == '\t')
    {
        auto nextControl = (this->focusedControlIndex + 1) % this->controls.size();

        if (nextControl != this->focusedControlIndex)
            this->SwitchFocus(nextControl);

        input.handled = true;
    }
}

void terminal::ContainerBase::HandleMouse(MouseInput &input)
{
    this->ControlBase::HandleMouse(input);

    if (input.handled)
        return;

    auto click = util::Point(input.cx, input.cy);

    if (this->focusedControlIndex >= 0 &&
        this->controls[this->focusedControlIndex]->GetBounds().Contains(click))
    {
        this->controls[focusedControlIndex]->HandleMouse(input);
    }
    else
    {
        bool controlHit = false;

        for (size_t i = 0; i < this->controls.size(); i++)
        {
            const auto &control = this->controls[i];

            if (control->GetBounds().Contains(click))
            {
                this->SwitchFocus(i);
                control->HandleMouse(input);
                controlHit = true;
                break;
            }
        }

        if (!controlHit)
        {
            this->SwitchFocus(-1);
            input.handled = true;
        }
    }
}

void terminal::ContainerBase::HandleZIndexChanged(int)
{
}

void terminal::ContainerBase::HandleTabIndexChanged(int)
{
}

void terminal::ContainerBase::Render(Canvas &canvas)
{
    this->terminal::ControlBase::Render(canvas);

    for (auto i = this->controls.begin(), end = this->controls.end(); i != end; i++)
    {
        (*i)->Render(canvas);
    }
}

void terminal::ContainerBase::Add(terminal::ControlBase *control)
{
    if (this->controls.empty())
    {
        this->controls.push_back(control);
        this->focusedControlIndex = 0;
        control->HandleFocusAquired();
    }
    else
    {
        this->controls.push_back(control);
    }

    control->HandleAddToControl(this);
}

void terminal::ContainerBase::SwitchFocus(int next)
{
    if (this->focusedControlIndex > 0)
    {
        this->controls[this->focusedControlIndex]->HandleFocusLost();
    }

    this->focusedControlIndex = next;
    TerminalView::GetInstance()->SetCursorMode(terminal::CursorMode::Invisible);

    if (this->focusedControlIndex > 0)
    {
        this->controls[this->focusedControlIndex]->HandleFocusAquired();
    }
}

const terminal::ControlBase *terminal::ContainerBase::GetFocusedControl() const
{
    if (this->focusedControlIndex == -1)
        return nullptr;

    return this->controls[this->focusedControlIndex];
}

terminal::ControlBase *terminal::ContainerBase::GetFocusedControl()
{
    if (this->focusedControlIndex == -1)
        return nullptr;

    return this->controls[this->focusedControlIndex];
}

size_t terminal::ContainerBase::GetFocusedControlIndex() const
{
    return this->focusedControlIndex;
}

void terminal::ContainerBase::RestoreLayout()
{
}
