#include "terminal.hpp"

terminal::control_base::control_base() : bounds(0, 0, 0, 0),
                                         parent(nullptr),
                                         z_index(0),
                                         has_focus(false)
{
}

terminal::control_base::~control_base()
{
}

terminal::control_base *terminal::control_base::get_parent()
{
    return this->parent;
}

const terminal::control_base *terminal::control_base::get_parent() const
{
    return this->parent;
}

bool terminal::control_base::has_parent() const
{
    return this->parent != nullptr;
}

const util::rectangle &terminal::control_base::get_bounds() const
{
    return this->bounds;
}

void terminal::control_base::set_bounds(const util::rectangle &bounds)
{
    this->bounds = bounds;
}

void terminal::control_base::set_z_index(int zIndex)
{
    this->z_index = zIndex;
}

int terminal::control_base::get_z_index() const
{
    return this->z_index;
}

std::string &terminal::control_base::get_text()
{
    return this->text;
}

const std::string &terminal::control_base::get_text() const
{
    return this->text;
}

void terminal::control_base::set_text(const std::string &text)
{
    this->text = text;
}

void terminal::control_base::handle_focus_aquired()
{
}

void terminal::control_base::handle_focus_lost()
{
}

void terminal::control_base::handle_key(key_input &)
{
}

void terminal::control_base::handle_mouse(mouse_input &)
{
}

void terminal::control_base::handle_add_to_control(control_base *)
{
}

void terminal::control_base::render(const util::rectangle &, terminal::canvas &)
{
}
