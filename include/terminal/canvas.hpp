#pragma once

#include <string>

#include "terminal_view.hpp"
#include "graphics/color.hpp"

namespace terminal
{
class canvas
{
  private:
    terminal_view *view;
    util::dimension size;
    util::rectangle clipped_area;
    util::point origin;

    int fg_color;
    util::color real_fg_color;
    int bg_color;
    util::color real_bg_color;
    bool color_changed;

    terminal::output_attribute active_attributes;
    bool active_attributes_changed;

    bool multiple_colors_supported;

  public:
    canvas(terminal_view *);
    canvas(const canvas &);

    terminal::canvas &draw_vertical_line(const util::point &, int length, char c);
    terminal::canvas &draw_horizontal_line(const util::point &, int y, char c);
    terminal::canvas &draw_box(const util::rectangle &, char horizontal, char vertical, char cornor);
    terminal::canvas &draw_box(const util::rectangle &, char c);
    terminal::canvas &fill(const util::rectangle &, char c);
    terminal::canvas &clear(char c);
    terminal::canvas &clear();
    terminal::canvas &draw_string(const util::point &, const std::string &);

    const util::dimension &get_size() const;
    const util::point &get_origin() const;
    const util::rectangle &get_clipped_area() const;
    const util::color &get_active_foreground_color() const;
    const util::color &get_active_background_color() const;
    terminal::output_attribute get_active_attributes() const;

    void set_origin(const util::point &);
    void clip_area(const util::dimension &);
    void clip_area(const util::rectangle &);
    void disable_clip();
    void enable_attribute(terminal::output_attribute);
    void disable_attribute(terminal::output_attribute);
    void set_foreground_color(const util::color &);
    void set_background_color(const util::color &);
    void set_foreground_color(int);
    void set_background_color(int);
    void reset_foreground_color();
    void reset_background_color();

    void flush();
};
} // namespace terminal