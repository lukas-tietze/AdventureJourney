#include "Test.hpp"

assert::assert_exception::assert_exception(const std::string &msg) : std::runtime_error(msg)
{
}

void assert::fail()
{
    throw assert_exception("Fail");
}

void assert::is_true(bool x)
{
    if (!x)
    {
        throw assert_exception("Value is not true!");
    }
}

void assert::is_false(bool x)
{
    if (x)
    {
        throw assert_exception("Value is not false!");
    }
}