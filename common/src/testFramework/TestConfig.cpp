#include <thread>

#include "Test.hpp"

test::TestConfig::TestConfig() : breakAfterFirstFailure(false),
                                 threadCount(1),
                                 timeout(-1),
                                 quiet(false),
                                 showOnlyFailed(false)

{
}

test::TestConfig::TestConfig(bool breakAfterFirstFailure,
                             uint threadCount,
                             long timeout,
                             bool quiet,
                             bool showOnlyFailed) : breakAfterFirstFailure(breakAfterFirstFailure),
                                                    threadCount(threadCount),
                                                    timeout(timeout),
                                                    quiet(quiet),
                                                    showOnlyFailed(showOnlyFailed)
{
}

test::TestConfig test::TestConfig::InitFromArgs(int argc, char **argv)
{
    test::TestConfig res;

    for (int i = 0; i < argc; i++)
    {
        auto arg = std::string(argv[i]);

        if (arg.length() >= 2 && arg[0] == '-')
        {
            switch (arg[1])
            {
            case 'p':
                if (arg.length() > 2)
                    res.threadCount = strtol(arg.data() + 1, nullptr, 10);
                else
                    res.threadCount = std::thread::hardware_concurrency();

                if (res.threadCount == 0)
                    res.threadCount = 1;
                break;
            case 't':
                res.timeout = strtol(arg.data() + 1, nullptr, 10);
                break;
            case 'b':
                res.breakAfterFirstFailure = true;
                break;
            case 'f':
                res.showOnlyFailed = true;
                break;
            case 'q':
                res.quiet = true;
                break;
            case 'h':
                std::printf("-p    run with recommended number of threads\n");
                std::printf("-p[x] run with x threads\n");
                std::printf("-t[x] timeout after x milli seconds\n");
                std::printf("-b    break after first failed test\n");
                std::printf("-q    ");
                std::printf("-h    show help\n");
                break;
            default:
                std::printf("Unknown argument %s\n", arg.c_str());
                break;
            }
        }
    }

    return res;
}

bool test::TestConfig::IsBreakAfterFirstFailureEnabled() const
{
    return this->breakAfterFirstFailure;
}

uint test::TestConfig::GetThreadCount() const
{
    return this->threadCount;
}

long test::TestConfig::GetTimeout() const
{
    return this->timeout;
}

bool test::TestConfig::IsQuietEnabled() const
{
    return this->quiet;
}

bool test::TestConfig::IsShowOnlyFailedEnabled() const
{
    return this->showOnlyFailed;
}
