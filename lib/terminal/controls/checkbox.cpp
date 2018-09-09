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
    if (input.key == ' ')
        this->switch_check_state();
}

void terminal::checkbox::handle_mouse(mouse_input &input)
{
    if (input.action == mouse_action::Button1Clicked)
        this->switch_check_state();
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

    switch (this->state)
    {
    case check_state::Checked:
        c.draw_string(util::point(bounds.get_min_x(), line), "X|");
        break;
    case check_state::Midway:
        c.draw_string(util::point(bounds.get_min_x(), line), "O|");
        break;
    case check_state::Unchecked:
        c.draw_string(util::point(bounds.get_min_x(), line), " |");
        break;
    }
}

void terminal::checkbox::switch_check_state()
{
    if (this->threeway_mode)
    {
        switch (this->state)
        {
        case check_state::Checked:
        case check_state::Midway:
            this->set_check_state(check_state::Unchecked);
            break;
        case check_state::Unchecked:
            this->set_check_state(check_state::Checked);
            break;
        }
    }
    else
    {
        this->set_checked(!this->is_checked());
    }
}
