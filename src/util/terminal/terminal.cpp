#include <string>
#include <ncurses.h>

#include "terminal.hpp"

util::terminal_view::terminal_view(int width, int height) : m_width(width),
                                                            m_height(height)
{
    m_window = newwin(m_width, m_height, 0, 0);
    box(m_window, 0, 0);
    wrefresh(m_window);
    refresh();
}

util::terminal_view::~terminal_view()
{
    wrefresh(m_window);
    delwin(m_window);
    refresh();
}

void util::terminal_view::set_input_mode(input_mode mode)
{
}

void util::terminal_view::set_echo(bool enableEcho)
{
    if (enableEcho)
    {
        echo();
    }
    else
    {
        noecho();
    }
}

char util::terminal_view::read_char()
{
    return getch();
}

std::string util::terminal_view::read_line()
{   
    getstr();
}

void util::terminal_view::print(const std::string &text)
{
    wprintw(m_window, text.c_str());
    wrefresh(m_window);
}

void util::terminal_view::print(const std::string &text, int x, int y)
{
    mvwprintw(m_window, x, y, text.c_str());
    wrefresh(m_window);
}

void util::terminal_view::print(char c)
{
    waddch(m_window, c);
    wrefresh(m_window);
}