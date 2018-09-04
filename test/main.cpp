#include <vector>
#include <cstdio>
#include <iostream>

#include "test.hpp"
#include "config.hpp"

int main(int argc, char **argv)
{
    test::test_collection tests;

    tests.push_back(test::test_run(new test::simple_test("simple tokenizing", &test::json::test_simple_tokenizing)));
    tests.push_back(test::test_run(new test::simple_test("basic color definitions", &test::color::test_basic_color_values)));

    for (auto &testRun : tests)
    {
        testRun.execute();
        util::printr(testRun);
    }

    #ifdef DEBUG
        std::printf("debug is active")
    #endif

    return 0;
}