#include <string>
#include <vector>
#include <iostream>
#include <pthread.h>
#include <cstdio>
#include <ncurses.h>

namespace
{
} // namespace

int main()
{
    start_color();
    initscr();

    noecho();
    cbreak();

    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_BLUE);

    addch('x');
    addch(static_cast<int>('x') & COLOR_PAIR(1));
    addch(static_cast<int>('x') & COLOR_PAIR(2));
    addch(static_cast<int>('x') & COLOR_PAIR(3));

    getch();

    endwin();
}