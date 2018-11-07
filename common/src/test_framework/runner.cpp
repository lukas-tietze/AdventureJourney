#include <thread>

#include "test.hpp"

void run_test_thread(test::test_collection tests, const test::test_config config, uint start)
{
    int end = tests.size();
    int step = end % config.get_thread_count();

    for (int i = start; i < end; i += step)
    {
        auto test = tests[i];

        test.execute();

        if (!test.is_good() || !config.is_show_only_failed_enabled())
        {
            util::printr(test);
        }
    }
}

int test::run_tests(test::test_collection &tests, const test::test_config &config)
{
    std::vector<std::thread> test_threads;

    if (!config.is_quiet_enabled())
    {
        std::printf("|-------------------------------------\n");
        std::printf("|timeout:             %s\n", config.get_timeout() >= 0 ? std::to_string(config.get_timeout()).c_str() : "-");
        std::printf("|tests:               %zu\n", tests.size());
        std::printf("|threads:             %u\n", config.get_thread_count());
        std::printf("|quiet:               %s\n", config.is_quiet_enabled() ? "true" : "false");
        std::printf("|break after failure: %s\n", config.is_break_after_first_failure_enabled() ? "true" : "false");
        std::printf("|show only failed:    %s\n", config.is_show_only_failed_enabled() ? "true" : "false");
        std::printf("|-------------------------------------\n\n");
    }

    clock_t start = std::clock();
    uint good = 0;

    if (config.get_thread_count() == 1)
    {
        for (auto &testRun : tests)
        {
            testRun.execute();

            if (testRun.is_good())
                good++;

            util::printr(testRun);
        }
    }
    else
    {
        for (uint i = 0; i < config.get_thread_count(); i++)
        {
            test_threads.push_back(std::thread(&run_test_thread, tests, config, i));
        }

        for (uint i = 0; i < config.get_thread_count(); i++)
        {
            test_threads[i].join();
        }
    }

    clock_t end = std::clock();
    uint failed = tests.size() - good;

    std::printf("\nFinished in %fms\n%u good (%.2f%%)\n%u failed (%.2f%%)\n",
                util::clock_to_ms(end - start),
                good,
                (double)good / (double)tests.size() * 100.0,
                failed,
                (double)failed / (double)tests.size() * 100.0);

    return failed;
}