#ifndef TEST_HPP
#define TEST_HPP

#include <string>
#include <ctime>
#include <iostream>

#include "util.hpp"

namespace test
{
typedef int (*test_function)();

class test_base
{
  private:
    std::string name;

  public:
    test_base(const std::string &name);
    virtual ~test_base();

    const std::string &get_name() const;

    virtual void init();
    virtual void run() = 0;
    virtual void dispose();
};

class simple_test : public test_base
{
  private:
    test_function func;

  public:
    simple_test(const std::string &name, test_function func);

    void run();
};

class test_run
{
  private:
    test_base *test;
    std::string message;
    bool good;
    clock_t start;
    clock_t end;

  public:
    test_run(test_base *test);
    ~test_run();

    void execute();

    double get_time_ms() const;
    clock_t get_time() const;
    bool is_good() const;
    bool is_started() const;
    bool is_finished() const;
    const std::string &get_message() const;

    friend std::ostream &operator<<(std::ostream &, const test_run &testRun);
};

std::ostream &operator<<(std::ostream &, const test_run &testRun);

typedef std::vector<test_run> test_collection;

namespace json
{
int test_simple_tokenizing();
int test_complex_tokenizing();
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
void is_null(const void *);
void is_not_null(const void *);
void is_true(bool x);
void is_false(bool x);

template <class T>
void are_equal(const T &x, const T &y)
{
    if (!(x == y))
    {
        throw assert_exception(util::to_string(x) + " does not equal " + util::to_string(y) + "!");
    }
}

template <class T>
void are_not_equal(const T &x, const T &y)
{
    if (x == y)
    {
        throw assert_exception(util::to_string(x) + " does equal " + util::to_string(y) + "!");
    }
}

template <class T>
void is_greater(const T &x, const T &y)
{
    if (!(x > y))
    {
        throw assert_exception(util::to_string(x) + " is not greater than " + util::to_string(y) + "!");
    }
}

template <class T>
void is_equal_or_greater(const T &x, const T &y)
{
    if (!(x >= y))
    {
        throw assert_exception(util::to_string(x) + "is not greater than or equal to " + util::to_string(y) + "!");
    }
}

template <class T>
void is_less(const T &x, const T &y)
{
    if (!(x < y))
    {
        throw assert_exception(util::to_string(x) + "is not less than " + util::to_string(y) + "!");
    }
}

template <class T>
void is_equal_or_less(const T &x, const T &y)
{
    if (!(x <= y))
    {
        throw assert_exception(util::to_string(x) + "is not less than or equal to " + util::to_string(y) + "!");
    }
}

template<class T>
void is(void *obj)
{
    if(static_cast<T*>(obj) == nullptr)
    {
        throw assert_exception(util::to_string(&obj) + "is not of type " + typeid(T).name());
    }
}
} // namespace assert

#endif /*TEST_HPP*/