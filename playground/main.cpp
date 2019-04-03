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
util::Channel out;

template <class T>
void Foo(T &)
{
    out.WriteLine("I am not a pointer");
}

template <class T>
void Foo(T *)
{
    out.WriteLine("I am a pointer");
}
} // namespace

int main()
{
    int i = 0;

    Foo(&i);
}