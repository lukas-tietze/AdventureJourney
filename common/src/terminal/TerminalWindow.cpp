#include <algorithm>

#include "Terminal.hpp"

terminal::TerminalWindow::TerminalWindow() : controls(),
                                             focusedControlIndex(-1),
                                             loop(true),
                                             escapeKey(0),
                                             hasEscapeKey(false)
{
}

terminal::TerminalWindow::~TerminalWindow()
{
    while (!this->controls.empty())
    {
        delete this->controls.back();
        this->controls.pop_back();
    }
}

terminal::ControlBase *terminal::TerminalWindow::AddControl(terminal::ControlBase *control)
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

    return control;
}

void terminal::TerminalWindow::SwitchFocus(int next)
{
    this->controls[this->focusedControlIndex]->HandleFocusLost();
    this->focusedControlIndex = next;
    this->controls[this->focusedControlIndex]->HandleFocusAquired();
}

void terminal::TerminalWindow::Start(int escapeKey)
{
    this->escapeKey = escapeKey;
    this->hasEscapeKey = true;

    this->Start();
}

void terminal::TerminalWindow::Start()
{

    auto view = TerminalView::GetInstance();

    this->Render();

    while (this->loop)
    {
        auto key = view->ReadKey();

        if (key == '\t')
        {
            auto nextControl = (this->focusedControlIndex + 1) % this->controls.size();

            if (nextControl != this->focusedControlIndex)
                this->SwitchFocus(nextControl);
        }
        else if (this->hasEscapeKey && key == this->escapeKey)
        {
            this->loop = false;
        }
        else if (this->focusedControlIndex >= 0)
        {
            auto focusedControl = this->controls[this->focusedControlIndex];

            if (key == KEY_MOUSE)
            {
                MEVENT mouseEvent;
                if (getmouse(&mouseEvent) == OK)
                {
                    MouseInput input;
                    input.cx = mouseEvent.x;
                    input.cy = mouseEvent.y;
                    input.handled = false;
                    input.action = static_cast<MouseAction>(mouseEvent.bstate);

                    auto location = util::Point(input.cx, input.cy);

                    if (focusedControl->GetBounds().Contains(location))
                    {
                        this->controls[this->focusedControlIndex]->HandleMouse(input);
                    }
                    else
                    {
                        for (size_t i = 0; i < this->controls.size(); i++)
                        {
                            auto control = this->controls[i];

                            if (control->GetBounds().Contains(location))
                            {
                                this->SwitchFocus(i);
                                control->HandleMouse(input);
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                KeyInput input;
                input.handled = false;
                input.key = key;

                focusedControl->HandleKey(input);
            }
        }

        this->Render();
    }
}

void terminal::TerminalWindow::Quit()
{
    this->loop = false;
}

void terminal::TerminalWindow::Render()
{
    auto view = TerminalView::GetInstance();
    auto bounds = util::Rectangle(0, 0, view->GetSize());
    auto canvas = terminal::Canvas(view);

    canvas.Clear();

    for (auto i = this->controls.begin(), end = this->controls.end(); i != end; i++)
    {
        canvas.ClipArea(bounds.Intersect((*i)->GetBounds()));

        (*i)->Render(canvas);
    }
}

terminal::ControlBase *terminal::TerminalWindow::GetFocusedControl() const
{
    if (this->focusedControlIndex == -1)
        return nullptr;

    return this->controls[this->focusedControlIndex];
}