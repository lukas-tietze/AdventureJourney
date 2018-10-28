#include "test.hpp"

test::simple_test::simple_test(const std::string &name, test_function func) : test_base(name),
                                                                              func(func)
{
}

void test::simple_test::run()
{
    (*func)();
}