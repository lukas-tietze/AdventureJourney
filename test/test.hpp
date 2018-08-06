#ifndef TEST_HPP
#define TEST_HPP

#include <string>

namespace test
{
    struct test_result
    {
        bool good;
        std::string error_message;
        clock_t length;
    };

    typedef test_result (*test_function)();

    test_result run_test(test_function f);
}

#endif /*TEST_HPP*/