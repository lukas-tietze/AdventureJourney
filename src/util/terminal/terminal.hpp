#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <string>
#include <ncurses.h>

namespace util
{
enum class input_mode
{
    RAW,
    BREAK,
};

class terminal_view
{
  private:
    WINDOW *m_window;
    int m_width;
    int m_height;
    char m_input_buf[4096];

  public:
    terminal_view(int width, int height);
    ~terminal_view();

    void set_input_mode(input_mode mode);
    void set_echo(bool echo);

    char read_char();
    std::string read_line();

    void print(const std::string &text);
    void print(const std::string &text, int x, int y);
    void print(char c);
};
} // namespace util

#endif /*TERMINAL_HPP*/