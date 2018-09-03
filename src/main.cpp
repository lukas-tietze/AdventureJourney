#include <cstdio>
#include <string>

#include "terminal.hpp"
#include "data/string.hpp"

int run()
{
    terminal::terminal_view *v = terminal::terminal_view::get_instance();

    v->set_echo(false);
    v->set_input_mode(terminal::input_mode::BREAK);

    int key;

    do
    {
        v->maximise();

        terminal::canvas c(v);
        c.clear();
        c.draw_string(util::point(10, 3), "current terminal size is: " + util::to_string(c.get_size()));
        c.draw_string(util::point(10, 4), "number of supported colors:" + util::to_string(c.get_supported_colors()));
        c.draw_string(util::point(10, 5), "number of supported color pairs:" + util::to_string(c.get_supported_color_pairs()));
        c.draw_box(util::rectangle(1, 1, c.get_size().get_width() - 2, c.get_size().get_height() - 2), '-', '|', '+');
        c.draw_box(util::rectangle(0, 0, 4, 4), '-', '|', '+');
        c.flush();

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