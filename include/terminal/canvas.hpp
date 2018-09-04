#pragma once

#include <string>
#include <vector>

#include "terminal_view.hpp"
#include "graphics/color.hpp"

namespace terminal
{
struct pattern_item final
{
    int length;
    char symbol;
    bool use_custom_color;
    util::color custom_color;
    bool use_custom_attributes;
    terminal::output_attribute custom_attributes;
};

class pattern_iterator final
{
  private:
    pattern_iterator();
    pattern_iterator(const pattern_iterator &);

  public:
    const pattern_item &operator*() const;
    pattern_iterator operator++() const;
    bool operator==(const pattern_iterator &) const;
    bool operator!=(const pattern_iterator &) const;
};

class pattern final
{
  private:
    std::vector<pattern_item> items;
    uint total_length;

  public:
    pattern();
    pattern(const pattern &);

    pattern &push(const pattern_item &);
    pattern &push(char c);
    pattern &push(char c, int count);
    pattern &push(char c, terminal::output_attribute);
    pattern &push(char c, int count, terminal::output_attribute);
    pattern &push(char c, const util::color &);
    pattern &push(char c, int count, const util::color &);
    pattern &push(char c, const util::color &, terminal::output_attribute);
    pattern &push(char c, int count, const util::color &, terminal::output_attribute);
    pattern &push_ec(char c, int color);
    pattern &push_ec(char c, int count, int color);
    pattern &push_ec(char c, int, terminal::output_attribute);
    pattern &push_ec(char c, int count, int color, terminal::output_attribute);

    void pop();
    uint get_total_length();
    uint get_item_count();

    pattern_iterator begin() const;
    pattern_iterator end() const;
};

class canvas
{
  private:
    terminal_view *view;
    util::dimension size;
    util::rectangle clipped_area;
    util::point origin;

  public:
    canvas(terminal_view *);
    canvas(const canvas &);

    terminal::canvas &draw_vertical_line(const util::point &, int length, char c);
    terminal::canvas &draw_vertical_line(const util::point &, int length, char c, int color);

    terminal::canvas &draw_horizontal_line(const util::point &, int y, char c);
    terminal::canvas &draw_horizontal_line(const util::point &, int y, char c, int color);

    terminal::canvas &draw_box(const util::rectangle &, char horizontal, char vertical, char cornor);
    terminal::canvas &draw_box(const util::rectangle &, char horizontal, char vertical, char cornor, int color);
    terminal::canvas &draw_box(const util::rectangle &, char horizontal, int hColor, char vertical, int vColor, char cornor, int cColor);

    terminal::canvas &draw_box(const util::rectangle &, char c);
    terminal::canvas &draw_box(const util::rectangle &, char c, int color);

    terminal::canvas &draw_string(const util::point &, const std::string &);
    terminal::canvas &draw_string(const util::point &, const std::string &, int color);
    terminal::canvas &draw_string(const util::point &, const std::string &, terminal::output_attribute attributes);
    terminal::canvas &draw_string(const util::point &, const std::string &, int color, terminal::output_attribute attributes);

    terminal::canvas &fill(const util::rectangle &, char c);
    terminal::canvas &clear(char c);
    terminal::canvas &clear();

    const util::dimension &get_size() const;
    const util::point &get_origin() const;
    const util::rectangle &get_clipped_area() const;

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
    void set_active_color_pair(short);
    void reset_foreground_color();
    void reset_background_color();

    void flush();

    terminal_view *get_view() const;

    short add_color(const util::color &);
    void set_color(short, const util::color &);
    short add_color_pair(const util::color &fg, const util::color &bg);
    short add_color_pair(short, short);
    void set_color_pair(short, short, short);
    short find_color_pair(short, short);
};
} // namespace terminal