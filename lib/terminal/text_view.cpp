#include "terminal.hpp"

terminal::text_view::text_view() : control_base()
{
}

terminal::text_view::text_view(const std::string &text) : control_base()
{
    this->set_text(text);
}

terminal::text_view::~text_view()
{
}

void terminal::text_view::handle_focus_aquired()
{
}

void terminal::text_view::handle_focus_lost()
{
}

void terminal::text_view::handle_key(key_input &)
{
}

void terminal::text_view::handle_mouse(mouse_input &)
{
}

void terminal::text_view::handle_add_to_control(control_base *)
{
}

void terminal::text_view::render(const util::rectangle &, canvas &)
{
}