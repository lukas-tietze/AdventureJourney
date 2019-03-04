#include <string>
#include <vector>
#include <iostream>
#include <pthread.h>
#include <cstdio>

bool stop = false;

void *print(void *)
{
    while (!stop)
    {
        std::printf("waiting...\n");
    }
}

void *read(void *)
{
    char in[4096];

    while (!stop)
    {
        std::scanf("%s\n", in);
        std::printf("read input %s\n", in);
        stop = true;
    }
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, nullptr, &print, nullptr);
    pthread_create(&t2, nullptr, &read, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
}