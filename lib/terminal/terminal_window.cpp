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

void terminal::terminal_window::switch_focus(int next)
{
    this->controls[this->focused_control_index]->handle_focus_lost();
    this->focused_control_index = next;
    this->controls[this->focused_control_index]->handle_focus_aquired();
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
                this->switch_focus(nextControl);
        }
        else if (this->focused_control_index >= 0)
        {
            auto focusedControl = this->controls[this->focused_control_index];

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

                    auto location = util::point(input.cx, input.cy);

                    if (focusedControl->get_bounds().contains(location))
                    {
                        this->controls[this->focused_control_index]->handle_mouse(input);
                    }
                    else
                    {
                        for (int i = 0; i < this->controls.size(); i++)
                        {
                            auto control = this->controls[i];

                            if (control->get_bounds().contains(location))
                            {
                                this->switch_focus(i);
                                control->handle_mouse(input);
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                terminal::key_input input;
                input.handled = false;
                input.key = key;

                focusedControl->handle_key(input);
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

        (*i)->render(canvas);
    }
}

terminal::control_base *terminal::terminal_window::get_focused_control() const
{
    if (this->focused_control_index == -1)
        return nullptr;

    return this->controls[this->focused_control_index];
}