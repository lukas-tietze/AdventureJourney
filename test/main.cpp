#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include <thread>
#include <map>

#include "test.hpp"
#include "config.hpp"
#include "defs.hpp"

namespace
{
test::test_collection tests;
bool break_after_first_failure = false;
uint thread_count = 1;
long timeout = -1;
std::vector<std::thread> test_threads;
} // namespace

void run_test_thread(int start)
{
    int step = tests.size() % thread_count;
    int end = tests.size();

    for (int i = start; i < end; i += step)
    {
        auto test = tests[i];

        test.execute();
        util::printr(test);
    }
}

int main(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        auto arg = std::string(argv[i]);

        if (arg.length() >= 2 && arg[0] == '-')
        {
            switch (arg[1])
            {
            case 'p':
                if (arg.length() > 2)
                    thread_count = strtol(arg.data() + 1, nullptr, 10);
                else
                    thread_count = std::thread::hardware_concurrency();

                if (thread_count == 0)
                    thread_count = 1;
                break;
            case 't':
                timeout = strtol(arg.data() + 1, nullptr, 10);
                break;
            case 'b':
                break_after_first_failure = true;
                break;
            }
        }
    }

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

    if (thread_count == 1)
    {
        for (auto &testRun : tests)
        {
            testRun.execute();
            util::printr(testRun);
        }
    }
    else
    {
        for (uint i = 0; i < thread_count; i++)
        {
            test_threads.push_back(std::thread{run_test_thread, i});
        }

        for (uint i = 0; i < thread_count; i++)
        {
            test_threads[i].join();
        }
    }

    return 0;
}