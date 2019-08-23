#include "Test.hpp"

test::SimpleTest::SimpleTest(const std::string &name, TestFunction func) : TestBase(name),
                                                                           func(func)
{
}

void test::SimpleTest::Run()
{
    (*func)();
}