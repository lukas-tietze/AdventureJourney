#include "terminal/controls/checkbox.hpp"

terminal::checkbox::checkbox() : control_base()
{
}

bool terminal::checkbox::is_checked() const
{
    return this->state == check_state::Checked;
}

void terminal::checkbox::set_checked(bool checked)
{
    this->state = checked ? check_state::Checked : check_state::Unchecked;
}

terminal::check_state terminal::checkbox::get_check_state() const
{
    return this->state;
}

void terminal::checkbox::set_check_state(check_state state)
{
    this->state = state;
}

void terminal::checkbox::set_threeway_mode_enabled(bool enabled)
{
    this->threeway_mode = enabled;
}

bool terminal::checkbox::is_threeeway_mode_enabled() const
{
    return this->threeway_mode;
}

void terminal::checkbox::handle_focus_aquired()
{
}

void terminal::checkbox::handle_focus_lost()
{
}

void terminal::checkbox::handle_key(key_input &input)
{
}

void terminal::checkbox::handle_mouse(mouse_input &input)
{
}

void terminal::checkbox::handle_add_to_control(container_base *control)
{
}

void terminal::checkbox::handle_tab_index_changed(int old)
{
}

void terminal::checkbox::handle_z_index_changed(int old)
{
}

void terminal::checkbox::render(canvas &c)
{
    auto bounds = this->get_bounds();
    auto line = (bounds.get_max_y() + bounds.get_min_y()) / 2;

    c.draw_box(this->get_bounds(), '-', '|', '+');

    if (this->threeway_mode)
    {
        switch (this->state)
        {
        }
    }
}
