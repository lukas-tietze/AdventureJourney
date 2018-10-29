#include "terminal/controls/textbox.hpp"

terminal::textbox::textbox() : control_base()
{
}

terminal::textbox::textbox(const std::string &text) : control_base()
{
    this->set_text(text);
}

terminal::textbox::~textbox()
{
}

void terminal::textbox::handle_mouse(terminal::mouse_input &action)
{
}

void terminal::textbox::handle_key(terminal::key_input &action)
{
}

void terminal::textbox::render(terminal::canvas &c)
{
    c.draw_string(this->get_bounds().get_location() + util::point(1, 1), this->get_text());
    c.draw_box(this->get_bounds(), '-', '|', '+');
}