#include <string>
#include <ncurses.h>
#include <cstdlib>

#include "interface.hpp"
#include "util/terminal/terminal.hpp"

int interactive_terminal::run_test(int argc, char **argv)
{
    initscr();

    util::terminal_view view(50, 50);
    // view.print("Hello World");
    // view.print("Hello World", 10, 10);
    view.print('a' | A_BOLD | A_UNDERLINE);

    view.read_char();

    endwin();

    return 0;
}