#ifndef TERMINAL_TERMINAL_VIEW_HPP
#define TERMINAL_TERMINAL_VIEW_HPP

#include <curses.h>
#include <string>

#include "values.hpp" 
#include "geometry.hpp"

namespace terminal
{
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
} // namespace terminal
#endif /*TERMINAL_TERMINAL_VIEW_HPP*/