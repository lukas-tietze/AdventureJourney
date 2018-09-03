#include "terminal.hpp"

terminal::terminal_window::terminal_window() : controls(10),
                                               focused_control_index(-1)
{
    // view.set_echo(false);
    // view.set_input_mode(terminal::input_mode::BREAK);
}

terminal::terminal_window::~terminal_window()
{
}

terminal::control_base *terminal::terminal_window::add_control(terminal::control_base *control)
{
    this->controls.push_back(control);

    return control;
}

void terminal::terminal_window::start()
{
}

terminal::control_base *terminal::terminal_window::get_focused_control() const
{
    if (this->focused_control_index == -1)
        return nullptr;

    return this->controls[this->focused_control_index];
}