#include <cstdio>

#include "terminal.hpp"
#include "data/string.hpp"

int run()
{
    terminal::terminal_view t(100, 200);
    t.set_input_mode(terminal::input_mode::BREAK);

    t.set_size(util::dimension(40, 40));

    t.print("(0, 0)", 10, 10);

    int key = t.read_key();

    while (key != 330)
    {
        t.print(util::format("You Pressed: %i", key), 10, 10);
        key = t.read_key();
    }

    t.print("Goodbye");
}

int main(int argc, char **argv)
{
    initscr();
    run();
    endwin();

    return 0;
}