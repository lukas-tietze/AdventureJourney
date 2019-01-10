#include <string>

#include <cstdio>
#include <cmath>

template <class T>
void foo(const T &)
{
    printf("printed by reference: %s\n", typeid(T).name());
}

template <class T>
void foo(const T *)
{
    printf("printed by pointer: %s\n", typeid(T).name());
}

int main()
{
    int i;

    foo(i);

    foo(&i);

    printf("\\n=>%i\n", static_cast<int>('\n'));

    return 0;
}