#ifndef TEST_HPP
#define TEST_HPP

#include <string>
#include <ctime>

#include "util.hpp"

namespace test
{
struct test_result
{
    test_result(const std::string &name, bool good) : name(name),
                                                      good(good)
    {
    }

    test_result() : name(""),
                    good(false)
    {
    }

    std::string name;
    bool good;
};

typedef test_result (*test_function)();

struct test_run
{
    test_run(test_function f) : function(f),
                                result(),
                                occurred_exception(),
                                exception_occurred(false),
                                duration(-1)
    {
    }

    test_function function;
    test_result result;
    std::exception occurred_exception;
    bool exception_occurred;
    clock_t duration;
};

typedef std::vector<test_run> test_collection;

namespace json
{
test::test_result test_simple_tokenizing();
test::test_result test_complex_tokenizing();
} // namespace json
} // namespace test

namespace assert
{
class assert_exception : public std::runtime_error
{
  public:
    assert_exception(const std::string &msg);
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

void is_true(bool x);
void is_false(bool x);

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