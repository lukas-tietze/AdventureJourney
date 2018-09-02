#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <string>
#include <vector>
#include <ncurses.h>

#include "data/collection/tupel.hpp"
#include "geometry/rectangle.hpp"
#include "graphics/color.hpp"

namespace terminal
{
enum class input_mode
{
    RAW,
    BREAK,
    LINE,
};

enum class resize_mode
{
    North = 1,
    South = 2,
    West = 4,
    East = 8,
    Horizontal = West | East,
    Vertical = North | South,
    All = North | South | West | East,
};

enum class output_attribute
{
    None = 0,
    Italic = 1,
    Bold = 2,
    Underline = 4,
    All = Italic | Bold | Underline,
};

struct key_input
{
    int key;
    bool handled;
};

struct mouse_input
{
    int cx;
    int cy;
    int button;
    bool handled;
};

class terminal_view
{
  private:
    WINDOW *window;
    int width;
    int height;
    char input_buf[4096];

    terminal::input_mode input_mode;
    bool echo_on;
    bool live_mode;

  protected:
    void on_terminal_property_changed();

  public:
    terminal_view();
    terminal_view(int width, int height);
    ~terminal_view();

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
};

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

    void buffer_color(const util::color &, bool);
    void read_buffered_color(bool);
    void buffer_data();

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
    int get_supported_colors() const;
    int get_supported_color_pairs() const;

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
    void reset_foreground_color(const util::color &);
    void reset_background_color(const util::color &);

    void flush();
};

class control_base
{
  private:
    util::rectangle bounds;
    control_base *parent;
    int z_index;
    bool has_focus;

  public:
    control_base();
    virtual ~control_base();

    control_base *get_parent();
    const control_base *get_parent() const;

    bool has_parent() const;
    const util::rectangle &get_bounds() const;
    void set_bounds(const util::rectangle &);
    void set_z_index(int);
    int get_z_index() const;

    virtual void handle_focus_aquired();
    virtual void handle_focus_lost();
    virtual void handle_key(key_input &);
    virtual void handle_mouse(mouse_input &);
    virtual void handle_add_to_control(control_base *);

    virtual void render(const util::rectangle &, canvas &);
};

class terminal_window
{
  private:
    std::vector<terminal::control_base *> controls;
    int focused_control_index;
    terminal_view view;

  public:
    terminal_window();
    ~terminal_window();

    control_base *add_control(control_base *);

    void start();

    control_base *get_focused_control() const;
};

class text_control_base : public control_base
{
  public:
    text_control_base();
    text_control_base(const std::string &text);
    virtual ~text_control_base();

    std::string &get_text();
    const std::string &get_text() const;
    void set_text(const std::string &);

  private:
    std::string text;
};

class container_base : public control_base
{
};

class text_view : public text_control_base
{
  public:
    text_view();
    text_view(const std::string &);
    virtual ~text_view();

    virtual void handle_focus_aquired();
    virtual void handle_focus_lost();
    virtual void handle_key(key_input &);
    virtual void handle_mouse(mouse_input &);
    virtual void handle_add_to_control(control_base *);

    virtual void render(const util::rectangle &, canvas &);
};
} // namespace terminal

#endif /*TERMINAL_HPP*/