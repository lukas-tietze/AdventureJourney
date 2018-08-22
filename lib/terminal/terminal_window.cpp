#include "terminal.hpp"

terminal::terminal_window::terminal_window() : control_base()
{
}

terminal::terminal_window::~terminal_window()
{
}

void terminal::terminal_window::add_control(terminal::control_base *control)
{
    this->controls.push_back(control);
    control->handle_add_to_control(this);
}

void terminal::terminal_window::render(const util::rectangle &bounds, const terminal_view &view)
{
}

terminal::control_base *terminal::terminal_window::get_focused_control() const
{
    if (this->focused_control_index == -1)
        return nullptr;

    return this->controls[this->focused_control_index];
}