#include <string>
#include <ncurses.h>
#include <cstdlib>

#include "interface.hpp"
#include "util.hpp"

int interactive_terminal::run_test(int argc, char **argv)
{
    initscr();

    util::terminal::terminal_view view(50, 50);
    view.print(std::to_string(sizeof(util::color)).c_str());

    view.read_key();

    endwin();

    return 0;
}