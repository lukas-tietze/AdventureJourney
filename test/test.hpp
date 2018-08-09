#ifndef TEST_HPP
#define TEST_HPP

#include <string>
#include <ctime>

#include "util.hpp"

namespace test
{
struct test_result
{
    std::string name = "";
    bool good = false;
    int custom_error_code = -1;
    std::string custom_error_message = "";
};

typedef test_result (*test_function)();

struct test_run
{
    test_function function = nullptr;
    test_result result = test_result();
    std::exception occurred_exception = std::exception();
    bool exception_occurred = false;
    clock_t duration = 0;
};

typedef std::vector<test_run> test_collection;
} // namespace test

namespace assert
{
class assert_exception : public std::runtime_error
{
  public:
    assert_exception(const std::string &msg) : std::runtime_error(msg)
    {
    }
};

void fail();

template <class T>
void are_equal(const T &x, const T &y)
{
    if (!(x == y))
    {
        throw assert_exception("Values are not equal!");
    }
}

template <class T>
void are_not_equal(const T &x, const T &y)
{
    if (x == y)
    {
        throw assert_exception("Values are equal!");
    }
}

void is_true(bool x)
{
    if (!x)
    {
        throw assert_exception("Value is not true!");
    }
}

void is_false(bool x)
{
    if (x)
    {
        throw assert_exception("Value is not false!");
    }
}

template <class T>
void is_greater(const T &x, const T &y)
{
    if (!(x > y))
    {
        throw assert_exception("");
    }
}

template <class T>
void is_equal_or_greater(const T &x, const T &y)
{
    if (!(x >= y))
    {
        throw assert_exception("");
    }
}

template <class T>
void is_less(const T &x, const T &y)
{
    if (!(x < y))
    {
        throw assert_exception("");
    }
}

template <class T>
void is_equal_or_less(const T &x, const T &y)
{
    if (!(x <= y))
    {
        throw assert_exception("");
    }
}
} // namespace assert

#endif /*TEST_HPP*/