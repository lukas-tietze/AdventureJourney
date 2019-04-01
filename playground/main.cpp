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
    std::printf("%i", std::isspace('\n') ? 1 : 0);
}