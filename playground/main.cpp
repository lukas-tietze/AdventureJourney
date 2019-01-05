#include <string>

#include <cstdio>
#include <cmath>

void foo(const std::string &)
{
    std::printf("foo");
}

void foo(const char *)
{
    std::printf("bar");
}

int main()
{
    foo("abc");

    return 0;
}