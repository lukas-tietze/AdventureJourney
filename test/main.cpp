#include <vector>
#include <cstdio>
#include <iostream>

#include "test.hpp"
#include "config.hpp"

int main(int argc, char **argv)
{
    test::test_collection tests;

    tests.push_back(test::test_run(new test::simple_test("read expanded", &test::json_test::expanded_read)));
    tests.push_back(test::test_run(new test::simple_test("read compact", &test::json_test::compact_read)));
    tests.push_back(test::test_run(new test::simple_test("write expanded", &test::json_test::expanded_write)));
    tests.push_back(test::test_run(new test::simple_test("write compact", &test::json_test::compact_write)));
    tests.push_back(test::test_run(new test::simple_test("write and read", &test::json_test::read_write)));
    tests.push_back(test::test_run(new test::simple_test("basic color definitions", &test::color_test::basic_color_values)));
    tests.push_back(test::test_run(new test::simple_test("function event test", &test::event_test::function_events)));
    tests.push_back(test::test_run(new test::simple_test("listener event test", &test::event_test::listener_events)));
    tests.push_back(test::test_run(new test::simple_test("handler event test", &test::event_test::handler_events)));
    tests.push_back(test::test_run(new test::simple_test("member handler event test", &test::event_test::member_handler_events)));
    tests.push_back(test::test_run(new test::simple_test("rectangle test", &test::geometry_test::rectangle)));

    for (auto &testRun : tests)
    {
        testRun.execute();
        util::printr(testRun);
    }

    return 0;
}