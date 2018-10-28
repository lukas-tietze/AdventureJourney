#include "terminal.hpp"

terminal::container_base::container_base() : control_base()
{
}

terminal::container_base::~container_base()
{
}

void terminal::container_base::handle_child_z_index_changed(control_base *)
{
}

void terminal::container_base::handle_child_tab_index_changed(control_base *)
{
}

void terminal::container_base::handle_focus_aquired()
{
}

void terminal::container_base::handle_focus_lost()
{
}

void terminal::container_base::handle_key(key_input &)
{
}

void terminal::container_base::handle_mouse(mouse_input &)
{
}

void terminal::container_base::handle_add_to_control(container_base *)
{
}

void terminal::container_base::handle_z_index_changed(int)
{
}

void terminal::container_base::handle_tab_index_changed(int)
{
}

void terminal::container_base::render(canvas &)
{
}
