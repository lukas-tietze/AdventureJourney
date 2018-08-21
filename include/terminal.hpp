#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "data.hpp"

#include <string>
#include <ncurses.h>

namespace terminal
{
enum class input_mode
{
    RAW,
    BREAK,
    LINE,
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

    util::dimension get_buffer_size();
    bool set_buffer_size(const util::dimension &);
    util::dimension get_screen_size();
    bool set_screen_size(const util::dimension &);

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

  public:
    control_base();

    control_base *get_parent();
    const control_base *get_parent() const;
    bool has_parent() const;
    const util::rectangle &get_bounds() const;
    void set_bounds(const util::rectangle &);
    void set_z_index(int);
    int get_z_index() const;

    virtual void render(const util::rectangle &, const terminal_view &) = 0;
};

class terminal_window : public control_base
{
  public:
    terminal_window();

    void add_control(control_base *);
    virtual void render(const util::rectangle &, const terminal_view &);
};

class container_base : public control_base
{
};

class text_view : public container_base
{

};

} // namespace terminal

#endif /*TERMINAL_HPP*/