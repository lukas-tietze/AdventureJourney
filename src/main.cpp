#include <cstdio>

#include "terminal.hpp"
#include "data/string_conversions.hpp"

int main(int argc, char **argv)
{
    initscr();

    terminal::terminal_view t(100, 200);
    t.set_input_mode(terminal::input_mode::BREAK);

    t.set_size(util::dimension(40,40));

    t.print("(0, 0)", 10, 10);

    while(true)
        t.print(util::format("You Pressed: %i", t.read_key()));

    t.print("Goodbye World");

    refresh();
    endwin();

    return 0;
}