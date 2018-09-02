#include <string>
#include <ncurses.h>

#include "terminal.hpp"

terminal::terminal_view::terminal_view() : terminal_view(LINES, COLS)
{
    this->maximise(); 
    this->flush();
}

terminal::terminal_view::terminal_view(int width, int height) : width(width),
                                                                height(height)
{
    this->window = newwin(this->width, this->height, 0, 0);
    keypad(this->window, true);
    this->flush();
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

    if (this->live_mode)
        wrefresh(this->window);
}

void terminal::terminal_view::print(const std::string &text, int x, int y)
{
    mvwprintw(this->window, y, x, text.c_str());

    if (this->live_mode)
        wrefresh(this->window);
}

void terminal::terminal_view::print(char c)
{
    waddch(this->window, c);

    if (this->live_mode)
        wrefresh(this->window);
}

void terminal::terminal_view::print(char c, int x, int y)
{
    mvwaddch(this->window, y, x, c);

    if (this->live_mode)
        wrefresh(this->window);
}

void terminal::terminal_view::on_terminal_property_changed()
{
    wrefresh(this->window);
}

util::dimension terminal::terminal_view::get_size() const
{
    int x, y;

    getmaxyx(this->window, y, x);

    return util::dimension(x, y);
}

bool terminal::terminal_view::set_size(const util::dimension &dim)
{
    resizeterm(dim.get_height(), dim.get_width());
}

void terminal::terminal_view::set_live_mode(bool live)
{
    this->live_mode = live;
}

void terminal::terminal_view::clear(const util::rectangle &area)
{
    std::string buf(area.get_width(), ' ');
    auto liveRestore = this->live_mode;
    this->live_mode = false;

    for (int y = area.get_min_y(); y < area.get_max_y(); y++)
    {
        this->print(buf, area.get_min_x(), y);
    }

    this->flush();
    this->live_mode = liveRestore;
}

void terminal::terminal_view::flush()
{
    wrefresh(this->window);
    refresh();
}

void terminal::terminal_view::maximise()
{
    int x, y;
    getmaxyx(this->window, y, x);
    resize_term(y, x);
    wresize(this->window, y, x);
    this->flush();
}
