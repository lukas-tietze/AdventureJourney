#include <vector>
#include <cstdio>
#include <iostream>

#include "test.hpp"

int main(int argc, char **argv)
{
    // std::cout << "Hello world";
    std::printf("Hello world\n");

    test::test_collection tests;

    std::printf("init.\n");
    tests.push_back(test::test_run(new test::simple_test("simple tokenizing", &test::json::test_simple_tokenizing)));

    for (auto &testRun : tests)
    {
        std::printf("Testing.\n");
        // testRun.execute();

        std::printf("Testing..\n");

        util::printr(testRun);

        std::printf("Testing...\n");
    }

    return 0;
}