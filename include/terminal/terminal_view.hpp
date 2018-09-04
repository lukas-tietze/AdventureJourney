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
    typedef util::tupel2<int, int> color_pair;

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
    void set_active_attributes(terminal::output_attribute);
    output_attribute get_active_attributes() const;

    void set_active_color_pair(int);
    void set_background_color_pair(int);
    int get_active_color_pair() const;
    int get_active_background() const;
    const color_pair &get_content(int id) const;
    const util::color &get_color(int id) const;

    int get_max_colors() const;
    int get_used_colors() const;
    int get_max_color_pairs() const;
    int get_used_color_pairs() const;
    bool can_change_colors() const;

    int add_color(const util::color &);
    void set_color(int, const util::color &);
    int find(const util::color &);
    int add_color_pair(const util::color &fg, const util::color &bg);
    int add_color_pair(int, int);
    void set_color_pair(int, int, int);
    int find_color_pair(int, int);

    bool can_add_colors() const;
    bool can_add_color_pairs() const;

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
    int max_colors;
    int used_colors;
    color_pair *color_pairs;
    int active_color_pair;
    int active_background_color_pair;
    int max_color_pairs;
    int used_color_pairs;

    output_attribute active_attributes;

    terminal_view();
    terminal_view(int width, int height);
};
} // namespace terminal