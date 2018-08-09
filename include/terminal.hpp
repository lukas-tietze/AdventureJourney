#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "data.hpp"

#include <string>
#include <ncurses.h>

namespace util
{
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

    util::terminal::input_mode input_mode;
    bool echo_on;

  protected:
    void on_terminal_property_changed();

  public:
    terminal_view(int width, int height);
    ~terminal_view();

    void set_input_mode(util::terminal::input_mode mode);
    void set_echo(bool echo);

    int read_key();
    std::string read_line();

    bool read_key(long timeOut, int &result);
    bool read_line(long timeOut, std::string &result);

    void print(const std::string &text);
    void print(const std::string &text, int x, int y);
    void print(char c);
};

class control_base
{
  private:
    util::rectangle bounds;
    control_base *parent;
  public:
    
};

class container_base : public control_base
{

};

} // namespace terminal
} // namespace util

#endif /*TERMINAL_HPP*/