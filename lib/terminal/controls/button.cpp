#include "terminal/controls/button.hpp"

terminal::button::button() : control_base()
{
}

terminal::button::button(const std::string &text) : control_base()
{
    this->set_text(text);
}

terminal::button::~button()
{
}

void terminal::button::handle_mouse(terminal::mouse_input &action)
{
}

void terminal::button::handle_key(terminal::key_input &action)
{
}

void terminal::button::render(canvas &c)
{
    c.draw_string(this->get_bounds().get_location() + util::point(1, 1), this->get_text());
    c.draw_box(this->get_bounds(), '-', '|', '+');
}