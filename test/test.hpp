#pragma once

#include <string>
#include <ctime>
#include <vector>
#include <iostream>

#include "data/string.hpp"
#include "data/io.hpp"
#include "datetime/datetime_conversions.hpp"
#include "exception.hpp"

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

namespace json_test
{
int expanded_read();
int compact_read();
int expanded_write();
int compact_write();
int read_write();
} // namespace json_test
namespace color_test
{
int basic_color_values();
}
namespace event_test
{
int function_events();
int listener_events();
int handler_events();
int member_handler_events();
} // namespace event_test
namespace geometry_test
{
int rectangle();
}
} // namespace test

namespace assert
{
class assert_exception : public util::exception
{
  public:
    assert_exception(const std::string &msg, const std::string &customMsg);
};

void fail(const std::string &msg = "");
void is_null(const void *, const std::string &msg = "");
void is_not_null(const void *, const std::string &msg = "");
void is_true(bool x, const std::string &msg = "");
void is_false(bool x, const std::string &msg = "");

template <class T>
void are_equal(const T &x, const T &y, const std::string &msg = "")
{
    if (!(x == y))
    {
        throw assert_exception("Expected " + util::to_string(x) + ", got " + util::to_string(y) + "!", msg);
    }
}

template <class T>
void are_not_equal(const T &x, const T &y, const std::string &msg = "")
{
    if (x == y)
    {
        throw assert_exception(util::to_string(x) + " does equal " + util::to_string(y) + "!", msg);
    }
}

template <class T>
void is_greater(const T &x, const T &y, const std::string &msg = "")
{
    if (!(x > y))
    {
        throw assert_exception(util::to_string(x) + " is not greater than " + util::to_string(y) + "!", msg);
    }
}

template <class T>
void is_equal_or_greater(const T &x, const T &y, const std::string &msg = "")
{
    if (!(x >= y))
    {
        throw assert_exception(util::to_string(x) + "is not greater than or equal to " + util::to_string(y) + "!", msg);
    }
}

template <class T>
void is_less(const T &x, const T &y, const std::string &msg = "")
{
    if (!(x < y))
    {
        throw assert_exception(util::to_string(x) + "is not less than " + util::to_string(y) + "!", msg);
    }
}

template <class T>
void is_equal_or_less(const T &x, const T &y, const std::string &msg = "")
{
    if (!(x <= y))
    {
        throw assert_exception(util::to_string(x) + "is not less than or equal to " + util::to_string(y) + "!");
    }
}

template <class T>
void is(void *obj, const std::string &msg = "")
{
    if (static_cast<T *>(obj) == nullptr)
    {
        throw assert_exception(util::to_string(&obj) + "is not of type " + typeid(T).name(), msg);
    }
}
} // namespace assert