#include <string>
#include <ncurses.h>

#include "terminal.hpp"

terminal::terminal_view::terminal_view(int width, int height) : width(width),
                                                                      height(height)
{
    this->window = newwin(this->width, this->height, 0, 0);

    keypad(this->window, true);
    box(this->window, 0, 0);
    wrefresh(this->window);
    refresh();
}

terminal::terminal_view::~terminal_view()
{
    wrefresh(this->window);
    delwin(this->window);
    refresh();
}

void terminal::terminal_view::set_input_mode(terminal::input_mode mode)
{
    if (mode != this->input_mode)
    {
        switch (mode)
        {
        case input_mode::BREAK:
            raw();
            break;
        case input_mode::RAW:
            cbreak();
            break;
        case input_mode::LINE:
            nocbreak();
            break;
        default:
            throw std::exception();
        }

        this->input_mode = mode;
        this->on_terminal_property_changed();
    }
}

void terminal::terminal_view::set_echo(bool enableEcho)
{
    if (enableEcho != this->echo_on)
    {
        if (enableEcho)
        {
            echo();
        }
        else
        {
            noecho();
        }

        this->echo_on = enableEcho;
        this->on_terminal_property_changed();
    }
}

int terminal::terminal_view::read_key()
{
    return wgetch(this->window);
}

std::string terminal::terminal_view::read_line()
{
    wgetstr(this->window, this->input_buf);
    return std::string(this->input_buf);
}

bool terminal::terminal_view::read_key(long timeOut, int &result)
{
}

bool terminal::terminal_view::read_line(long timeOut, std::string &result)
{
}

void terminal::terminal_view::print(const std::string &text)
{
    wprintw(this->window, text.c_str());
    wrefresh(this->window);
}

void terminal::terminal_view::print(const std::string &text, int x, int y)
{
    mvwprintw(this->window, x, y, text.c_str());
    wrefresh(this->window);
}

void terminal::terminal_view::print(char c)
{
    waddch(this->window, c);
    wrefresh(this->window);
}

void terminal::terminal_view::on_terminal_property_changed()
{
    wrefresh(this->window);
}