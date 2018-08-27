#include <cstdio>

#include "terminal.hpp"
#include "data/string.hpp"

int run()
{
    terminal::terminal_view v;
    terminal::canvas c(&v);

    c.dr
}

int main(int argc, char **argv)
{
    initscr();
    run();
    endwin();

    return 0;
}