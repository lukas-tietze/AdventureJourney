#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <string>
#include <vector>
#include <ncurses.h>

#include "data/collection/tupel.hpp"
#include "geometry/rectangle.hpp"

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

  protected:
    void on_terminal_property_changed();

  public:
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
    void clear(int x, int y);
    void clear(const util::dimension &area);
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

    virtual void render(const util::rectangle &, const terminal_view &);
};

class terminal_window : public control_base
{
  private:
    std::vector<terminal::control_base *> controls;
    int focused_control_index;

  public:
    terminal_window();
    virtual ~terminal_window();

    void add_control(control_base *);
    virtual void render(const util::rectangle &, const terminal_view &);

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

    virtual void render(const util::rectangle &, const terminal_view &);
};

class canvas
{
  private:
    terminal_view *view;

  public:
    canvas();

    canvas &draw_vertical_line();
};
} // namespace terminal

#endif /*TERMINAL_HPP*/