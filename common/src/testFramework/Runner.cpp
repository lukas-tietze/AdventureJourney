#include <thread>
#include <csignal>

#include "Test.hpp"

namespace
{
void BindSignalHandlers()
{
}
} // namespace

void RunTestThread(test::TestCollection tests, const test::TestConfig config, uint start)
{
    int end = tests.size();
    int step = end % config.GetThreadCount();

    for (int i = start; i < end; i += step)
    {
        auto test = tests[i];

        test.Execute();

        if (!test.IsGood() || !config.IsShowOnlyFailedEnabled())
        {
            util::Print(test);
        }
    }
}

int test::RunTests(test::TestCollection &tests, const test::TestConfig &config)
{
    std::vector<std::thread> test_threads;

    if (!config.IsQuietEnabled())
    {
        std::printf("|-------------------------------------\n");
        std::printf("|timeout:             %s\n", config.GetTimeout() >= 0 ? std::to_string(config.GetTimeout()).c_str() : "-");
        std::printf("|tests:               %zu\n", tests.size());
        std::printf("|threads:             %u\n", config.GetThreadCount());
        std::printf("|quiet:               %s\n", config.IsQuietEnabled() ? "true" : "false");
        std::printf("|break after failure: %s\n", config.IsBreakAfterFirstFailureEnabled() ? "true" : "false");
        std::printf("|show only failed:    %s\n", config.IsShowOnlyFailedEnabled() ? "true" : "false");
        std::printf("|-------------------------------------\n\n");
    }

    clock_t start = std::clock();
    uint good = 0;

    if (config.GetThreadCount() == 1)
    {
        for (auto &testRun : tests)
        {
            testRun.Execute();

            if (testRun.IsGood())
                good++;

            util::Print(testRun);
        }
    }
    else
    {
        for (uint i = 0; i < config.GetThreadCount(); i++)
        {
            test_threads.push_back(std::thread(&RunTestThread, tests, config, i));
        }

        for (uint i = 0; i < config.GetThreadCount(); i++)
        {
            test_threads[i].join();
        }
    }

    clock_t end = std::clock();
    uint failed = tests.size() - good;

    std::printf("\nFinished in %fms\n%u good (%.2f%%)\n%u failed (%.2f%%)\n",
                util::ClockToMs(end - start),
                good,
                (double)good / (double)tests.size() * 100.0,
                failed,
                (double)failed / (double)tests.size() * 100.0);

    return failed;
}