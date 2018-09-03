#include <cstdio>
#include <string>

#include "terminal.hpp"
#include "data/string.hpp"

int loop(terminal::terminal_view *v)
{
    // terminal::canvas c(v);
    // c.clear();
    // c.draw_string(util::point(10, 3), "current terminal size is: " + util::to_string(c.get_size()));
    // c.draw_string(util::point(10, 4), "number of supported colors:" + util::to_string(c.get_supported_colors()));
    // c.draw_string(util::point(10, 5), "number of supported color pairs:" + util::to_string(c.get_supported_color_pairs()));
    // c.draw_box(util::rectangle(1, 1, c.get_size().get_width() - 2, c.get_size().get_height() - 2), '-', '|', '+');
    // c.draw_box(util::rectangle(0, 0, 4, 4), '-', '|', '+');
    // c.flush();
}

int run()
{
    terminal::terminal_view *v = terminal::terminal_view::get_instance();

    v->set_echo(false);
    v->set_input_mode(terminal::input_mode::BREAK);

    int key;

    init_color(0, 1000, 0, 0);
    init_color(1, 0, 1000, 0);
    init_color(2, 0, 0, 1000);

    init_pair(1, 0, 1);
    init_pair(2, 1, 2);
    init_pair(3, 2, 0);

    color_set(1, nullptr);
    mvaddstr(5, 5, "Paar 0 - Invalid");

    color_set(2, nullptr);
    mvaddstr(6, 5, "Paar 1 - Green/Blue");

    color_set(3, nullptr);
    mvaddstr(7, 5, "Paar 2 - Blue/Red");

    do
    {
        v->maximise();

        loop(v);

        key = v->read_key();
    } while (key != 'q');
}

int main(int argc, char **argv)
{
    initscr();
    start_color();
    run();
    endwin();

    return 0;
}