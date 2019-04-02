#include <string>
#include <vector>
#include <iostream>
#include <pthread.h>
#include <cstdio>
#include <ncurses.h>

#include "data/String.hpp"
#include "data/Io.hpp"

namespace
{
int i = 0;

int &GetI()
{
    return i;
}
} // namespace

int main()
{
    util::Channel out;

    out.WriteLine("&i=%, &GetI=%", &i, &GetI());
}