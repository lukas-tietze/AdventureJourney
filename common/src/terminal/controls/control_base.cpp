#include "terminal.hpp"

int terminal::control_base::z_index_sorter::operator()(const control_base &a, const control_base &b)
{
    return a.z_index - b.z_index;
}

int terminal::control_base::tab_index_sorter::operator()(const control_base &a, const control_base &b)
{
    return a.tab_index - b.tab_index;
}

terminal::control_base::control_base() : bounds(0, 0, 0, 0),
                                         parent(nullptr),
                                         z_index(0),
                                         has_focus(false),
                                         visible(true),
                                         minimum_size(0, 0),
                                         maximum_size(std::numeric_limits<int>::max(), std::numeric_limits<int>::max())
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
    if (this->bounds != bounds)
    {
        this->handle_bounds_changed();
        this->set_bounds_core(bounds);
    }
}

void terminal::control_base::set_bounds_core(const util::rectangle &bounds)
{
    this->validate_bounds(this->bounds);
}

bool terminal::control_base::validate_bounds(util::rectangle &alternative)
{
    if (bounds.get_size().get_width() < this->minimum_size.get_width() ||
        bounds.get_size().get_height() < this->minimum_size.get_height() ||
        bounds.get_size().get_width() > this->maximum_size.get_width() ||
        bounds.get_size().get_height() > this->maximum_size.get_height())
    {
        alternative = util::rectangle(util::rectangle(bounds.get_location(), bounds.get_size().crop(this->minimum_size, this->maximum_size)));
    }
}

void terminal::control_base::set_z_index(int zIndex)
{
    if (this->z_index != zIndex)
    {
        this->set_z_index_core(zIndex);
        this->handle_z_index_changed();
    }
}

void terminal::control_base::set_z_index_core(int zIndex)
{
    this->z_index = zIndex;

    if (this->parent != nullptr)
    {
        // this->parent->invalidate();
    }
}

int terminal::control_base::get_z_index() const
{
    return this->z_index;
}

const std::string &terminal::control_base::get_text() const
{
    return this->text;
}

void terminal::control_base::set_text(const std::string &text)
{
    if (this->text != text)
    {
        this->set_text_core(text);
        this->handle_text_changed();
    }
}

void terminal::control_base::set_text_core(const std::string &text)
{
    this->text = text;
}

bool terminal::control_base::is_visible() const
{
    return this->visible;
}

void terminal::control_base::set_visibility(bool visible)
{
    this->visible = visible;
}

int terminal::control_base::get_tab_index() const
{
    return this->tab_index;
}

void terminal::control_base::set_tab_index(int tabIndex)
{
    this->tab_index = tabIndex;
}

const util::dimension &terminal::control_base::get_min_size() const
{
    return this->minimum_size;
}

const util::dimension &terminal::control_base::get_max_size() const
{
    return this->maximum_size;
}

void terminal::control_base::set_min_size(const util::dimension &size)
{
    this->minimum_size = size;

    if (this->bounds.get_size().get_height() < this->minimum_size.get_height() ||
        this->bounds.get_size().get_width() < this->minimum_size.get_width())
    {
        this->set_bounds_core(util::rectangle(
            this->bounds.get_location(),
            this->bounds.get_size().crop(this->minimum_size, this->maximum_size)));
    }
}

void terminal::control_base::set_max_size(const util::dimension &size)
{
    this->maximum_size = size;
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

void terminal::control_base::handle_add_to_control(container_base *)
{
}

void terminal::control_base::handle_tab_index_changed()
{
}

void terminal::control_base::handle_z_index_changed()
{
}

void terminal::control_base::handle_bounds_changed()
{
}

void terminal::control_base::handle_text_changed()
{
}