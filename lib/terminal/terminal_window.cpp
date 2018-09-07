#include <algorithm>

#include "terminal.hpp"

terminal::terminal_window::terminal_window() : controls(10),
                                               focused_control_index(-1),
                                               loop(true)
{
}

terminal::terminal_window::~terminal_window()
{
    while (!this->controls.empty())
    {
        delete this->controls.back();
        this->controls.pop_back();
    }
}

terminal::control_base *terminal::terminal_window::add_control(terminal::control_base *control)
{
    if (this->controls.empty())
    {
        this->controls.push_back(control);
        this->focused_control_index = 0;
        control->handle_focus_aquired();
    }
    else
    {
        this->controls.push_back(control);
    }

    control->handle_add_to_control(this);

    return control;
}

void terminal::terminal_window::start()
{
    auto view = terminal_view::get_instance();

    while (this->loop)
    {
        auto key = view->read_key();

        if (key == '\t')
        {
            auto nextControl = (this->focused_control_index + 1) % this->controls.size();

            if (nextControl != this->focused_control_index)
            {
                this->controls[this->focused_control_index]->handle_focus_lost();
                this->focused_control_index = nextControl;
                this->controls[this->focused_control_index]->handle_focus_aquired();
            }
        }
        else if (this->focused_control_index >= 0)
        {
            if (key == KEY_MOUSE)
            {
                MEVENT mouseEvent;
                if (getmouse(&mouseEvent) == OK)
                {
                    mouse_input input;
                    input.cx = mouseEvent.x;
                    input.cy = mouseEvent.y;
                    input.handled = false;
                    input.action = mouseEvent.bstate;

                    this->controls[this->focused_control_index]->handle_mouse(input);
                }
            }
            else
            {
                terminal::key_input input;
                input.handled = false;
                input.key = key;

                this->controls[this->focused_control_index]->handle_key(input);
            }
        }

        this->render();
    }
}

void terminal::terminal_window::quit()
{
    this->loop = false;
}

void terminal::terminal_window::render()
{
    auto view = terminal_view::get_instance();
    auto bounds = util::rectangle(0, 0, view->get_size());
    auto canvas = terminal::canvas(view);

    for (auto i = this->controls.begin(), end = this->controls.end(); i != end; i++)
    {
        canvas.clip_area(bounds.intersect((*i)->get_bounds()));

        (*i)->render(bounds, canvas);
    }
}

terminal::control_base *terminal::terminal_window::get_focused_control() const
{
    if (this->focused_control_index == -1)
        return nullptr;

    return this->controls[this->focused_control_index];
}