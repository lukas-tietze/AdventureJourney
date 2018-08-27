#include "terminal.hpp"
#include "data/helper.hpp"

terminal::canvas::canvas(terminal_view *view) : view(view),
                                                size(view->get_size()),
                                                clipped_area(0, 0, this->size),
                                                origin(0, 0),
                                                fg_color(COLOR_WHITE),
                                                real_fg_color(util::color_white),
                                                bg_color(COLOR_BLACK),
                                                real_bg_color(util::color_black),
                                                color_changed(false),
                                                active_attributes(terminal::output_attribute::None),
                                                active_attributes_changed(false),
                                                multiple_colors_supported(can_change_color())
{
}

terminal::canvas::canvas(const canvas &copy) : view(copy.view),
                                               size(copy.size),
                                               clipped_area(copy.clipped_area),
                                               origin(copy.origin),
                                               fg_color(copy.fg_color),
                                               real_fg_color(copy.real_fg_color),
                                               bg_color(copy.bg_color),
                                               real_bg_color(copy.real_bg_color),
                                               color_changed(copy.color_changed),
                                               active_attributes(copy.active_attributes),
                                               active_attributes_changed(copy.active_attributes_changed),
                                               multiple_colors_supported(copy.multiple_colors_supported)
{
}

terminal::canvas &terminal::canvas::draw_vertical_line(const util::point &p, int length, char c)
{
}

terminal::canvas &terminal::canvas::draw_horizontal_line(const util::point &p, int y, char c)
{
}

terminal::canvas &terminal::canvas::draw_box(const util::rectangle &p, char c)
{
}

terminal::canvas &terminal::canvas::fill(const util::rectangle &p, char c)
{
}

terminal::canvas &terminal::canvas::clear(char c)
{
}

terminal::canvas &terminal::canvas::clear()
{
}

terminal::canvas &terminal::canvas::draw_string(const util::point &p, const std::string &s)
{
}

const util::dimension &terminal::canvas::get_size() const
{
}

const util::point &terminal::canvas::get_origin() const
{
}

const util::rectangle &terminal::canvas::get_clipped_area() const
{
}

const util::color &terminal::canvas::get_active_foreground_color() const
{
    return this->real_fg_color;
}

const util::color &terminal::canvas::get_active_background_color() const
{
    return this->real_bg_color;
}

terminal::output_attribute terminal::canvas::get_active_attributes() const
{
    return this->active_attributes;
}

int terminal::canvas::get_supported_colors() const
{
    return COLORS;
}

void terminal::canvas::set_origin(const util::point &p)
{
    this->origin = p;
}

void terminal::canvas::clip_area(const util::dimension &d)
{
    this->clipped_area = util::rectangle(this->origin, d);
}

void terminal::canvas::clip_area(const util::rectangle &p)
{
    this->clipped_area = p;
}

void terminal::canvas::disable_clip()
{
    this->clipped_area = util::rectangle(this->origin, this->size);
}

void terminal::canvas::enable_attribute(terminal::output_attribute a)
{
    // this->active_attributes = (terminal::output_attribute)((int)this->active_attributes | (int)a);
    util::enable_flag(this->active_attributes, a);
    this->active_attributes_changed = true;
}

void terminal::canvas::disable_attribute(terminal::output_attribute a)
{
    // this->active_attributes = (terminal::output_attribute)((int)this->active_attributes & (~(int)a));
    util::disable_flag(this->active_attributes, a);
    this->active_attributes_changed = true;
}

void terminal::canvas::set_foreground_color(const util::color &c)
{
    this->buffer_color(c, true);
}

void terminal::canvas::set_background_color(const util::color &c)
{
    this->buffer_color(c, false);
}

void terminal::canvas::set_foreground_color(int c)
{
    this->fg_color = c;
    this->read_buffered_color(true);
}

void terminal::canvas::set_background_color(int c)
{
    this->bg_color = c;
    this->read_buffered_color(false);
}

void terminal::canvas::reset_foreground_color(const util::color &c)
{
    this->set_foreground_color(util::color_white);
}

void terminal::canvas::reset_background_color(const util::color &c)
{
    this->set_background_color(util::color_black);
}

void terminal::canvas::buffer_color(const util::color &c, bool fg)
{
}

void terminal::canvas::read_buffered_color(bool)
{
}

void terminal::canvas::buffer_data()
{
}

void terminal::canvas::flush()
{
}
