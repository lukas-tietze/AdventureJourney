#pragma once

#include <curses.h>
#include <string>

#include "data/collection/tupel.hpp"
#include "util.hpp"
#include "values.hpp"
#include "geometry.hpp"
#include "graphics/color.hpp"

namespace terminal
{
class terminal_view
{
  public:
    typedef util::tupel2<util::color, util::color> color_pair;

    ~terminal_view();

    static terminal_view *get_instance();
    static terminal_view *delete_instance();

    void set_input_mode(terminal::input_mode mode);
    void set_echo(bool echo);

    util::dimension get_size() const;
    bool set_size(const util::dimension &);

    int read_key();
    std::string read_line();

    bool read_key(long timeOut, int &result);
    bool read_line(long timeOut, std::string &result);

    void print(const std::string &text);
    void print(const std::string &text, int x, int y);
    void print(char c);
    void print(char c, int x, int y);
    void clear(const util::rectangle &area);
    void flush();

    void maximise();
    void set_live_mode(bool);

    void set_attribute(terminal::output_attribute, bool);
    void reset_attribtues();
    void attribute_on(terminal::output_attribute);
    void attribute_off(terminal::output_attribute);

    void set_active_color_pair(short);
    void set_background_color(short);

    short get_max_colors() const;
    short get_used_colors() const;
    short get_max_color_pairs() const;
    short get_used_color_pairs() const;
    bool can_change_colors() const;

    const util::color &get_color(short) const;
    short add_color(const util::color &);
    void set_color(short, const util::color &);
    short find(const util::color &);
    short add_color_pair(const util::color &fg, const util::color &bg);
    short add_color_pair(short, short);
    void set_color_pair(short, short, short);
    short find_color_pair(short, short);

    bool can_add_colors() const;
    bool can_add_color_pairs() const;

    const color_pair &get_active_color_pair() const;
    const color_pair &get_active_background() const;

  protected:
    void on_terminal_property_changed();

  private:
    static terminal_view *instance;

    WINDOW *window;
    int width;
    int height;
    char input_buf[4096];

    terminal::input_mode input_mode;
    bool echo_on;
    bool live_mode;

    util::color *colors;
    short max_colors;
    short used_colors;
    color_pair *color_pairs;
    short active_color_pair;
    short active_background_color_pair;
    short max_color_pairs;
    short used_color_pairs;

    terminal_view();
    terminal_view(int width, int height);
};
} // namespace terminal