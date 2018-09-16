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
bool quiet;
bool show_only_failed;
} // namespace

void run_test_thread(int start)
{
    int end = tests.size();
    int step = end % thread_count;

    for (int i = start; i < end; i += step)
    {
        auto test = tests[i];

        test.execute();

        if (!test.is_good() || !show_only_failed)
        {
            util::printr(test);
        }
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
            case 'f':
                show_only_failed = true;
                break;
            case 'q':
                quiet = true;
                break;
            case 'h':
                std::printf("-p    run with recommended number of threads\n");
                std::printf("-p[x] run with x threads\n");
                std::printf("-t[x] timeout after x milli seconds\n");
                std::printf("-b    break after first failed test\n");
                std::printf("-q    ");
                std::printf("-h    show help\n");
                return 0;
            }
        }
    }

    tests.push_back(test::test_run(new test::simple_test("test integrity", &test::json_test::integrity)));
    tests.push_back(test::test_run(new test::simple_test("read expanded", &test::json_test::expanded_read)));
    tests.push_back(test::test_run(new test::simple_test("read compact", &test::json_test::compact_read)));
    tests.push_back(test::test_run(new test::simple_test("write expanded", &test::json_test::expanded_write)));
    tests.push_back(test::test_run(new test::simple_test("write compact", &test::json_test::compact_write)));
    tests.push_back(test::test_run(new test::simple_test("read and write", &test::json_test::read_write)));
    tests.push_back(test::test_run(new test::simple_test("write and read", &test::json_test::write_read)));
    tests.push_back(test::test_run(new test::simple_test("string escaping", &test::json_test::string_escaping)));
    tests.push_back(test::test_run(new test::simple_test("number parsing", &test::json_test::number_parsing)));
    tests.push_back(test::test_run(new test::simple_test("basic color definitions", &test::color_test::basic_color_values)));
    tests.push_back(test::test_run(new test::simple_test("function event test", &test::event_test::function_events)));
    tests.push_back(test::test_run(new test::simple_test("listener event test", &test::event_test::listener_events)));
    tests.push_back(test::test_run(new test::simple_test("handler event test", &test::event_test::handler_events)));
    tests.push_back(test::test_run(new test::simple_test("member handler event test", &test::event_test::member_handler_events)));
    tests.push_back(test::test_run(new test::simple_test("rectangle test", &test::geometry_test::rectangle)));

    if (!quiet)
    {
        std::printf("|-------------------------------------\n");
        std::printf("|timeout:             %s\n", timeout >= 0 ? std::to_string(timeout).c_str() : "-");
        std::printf("|tests:               %zu\n", tests.size());
        std::printf("|threads:             %u\n", thread_count);
        std::printf("|quiet:               %s\n", quiet ? "true" : "false");
        std::printf("|break after failure: %s\n", break_after_first_failure ? "true" : "false");
        std::printf("|show only failed:    %s\n", show_only_failed ? "true" : "false");
        std::printf("|-------------------------------------\n\n");
    }

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