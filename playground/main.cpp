#include <string>

#include <cstdio>
#include <cmath>

int main()
{
    std::printf("round(0.5f)=%f", std::round(0.5f));
    std::printf("round(0.5)=%f", std::round(0.5));

    return 0;
}