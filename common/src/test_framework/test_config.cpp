#include <thread>

#include "test.hpp"

test::test_config::test_config() : break_after_first_failure(false),
                                   thread_count(1),
                                   timeout(-1),
                                   quiet(false),
                                   show_only_failed(false)

{
}

test::test_config::test_config(bool break_after_first_failure,
                               uint thread_count,
                               long timeout,
                               bool quiet,
                               bool show_only_failed) : break_after_first_failure(break_after_first_failure),
                                                        thread_count(thread_count),
                                                        timeout(timeout),
                                                        quiet(quiet),
                                                        show_only_failed(show_only_failed)
{
}

test::test_config test::test_config::init_from_args(int argc, char **argv)
{
    test::test_config res;

    for (int i = 0; i < argc; i++)
    {
        auto arg = std::string(argv[i]);

        if (arg.length() >= 2 && arg[0] == '-')
        {
            switch (arg[1])
            {
            case 'p':
                if (arg.length() > 2)
                    res.thread_count = strtol(arg.data() + 1, nullptr, 10);
                else
                    res.thread_count = std::thread::hardware_concurrency();

                if (res.thread_count == 0)
                    res.thread_count = 1;
                break;
            case 't':
                res.timeout = strtol(arg.data() + 1, nullptr, 10);
                break;
            case 'b':
                res.break_after_first_failure = true;
                break;
            case 'f':
                res.show_only_failed = true;
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

bool test::test_config::is_break_after_first_failure_enabled() const
{
    return this->break_after_first_failure;
}

uint test::test_config::get_thread_count() const
{
    return this->thread_count;
}

long test::test_config::get_timeout() const
{
    return this->timeout;
}

bool test::test_config::is_quiet_enabled() const
{
    return this->quiet;
}

bool test::test_config::is_show_only_failed_enabled() const
{
    return this->show_only_failed;
}
