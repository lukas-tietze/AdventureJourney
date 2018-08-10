#include <vector>

#include "test.hpp"

void gather_tests(test::test_collection &tests)
{
    tests.push_back(test::test_run(&test::json::test_simple_tokenizing));
    tests.push_back(test::test_run(&test::json::test_complex_tokenizing));
}

////TODO nochmal durchdenken
void execute_tests(test::test_collection &tests)
{
    clock_t start;
    clock_t end;
    test::test_result result;

    for (auto &test : tests)
    {
        try
        {
            start = clock();
            result = (*test.function)();
            end = clock();
        }
        catch (const std::exception &e)
        {
            end = clock();
            result.good = false;
            test.occurred_exception = e;
            test.exception_occurred = true;
        }

        test.duration = end - start;
        test.result = result;
    }
}

void print_results(test::test_collection &tests)
{
    auto successfullRuns = 0;

    for (const auto &test : tests)
    {
        if (test.result.good)
        {
            successfullRuns++;
        }
    }

    std::printf("Finished %i tests. %i/%i (%f%%) successfull.\n",
                tests.size(),
                successfullRuns,
                tests.size(),
                successfullRuns / (double)tests.size());

    for (const auto &test : tests)
    {
        if (test.result.good)
        {
            std::printf("[+] [%f] %s\n", util::clock_to_ms(test.duration), test.result.name.c_str());
        }
    }

    for (const auto &test : tests)
    {
        if (test.result.good)
        {
            std::printf("[+] [%f] %s\n", util::clock_to_ms(test.duration), test.result.name.c_str());
        }
    }
}

int main(int argc, char **argv)
{
    test::test_collection tests;

    gather_tests(tests);
    execute_tests(tests);
    print_results(tests);

    return 0;
}