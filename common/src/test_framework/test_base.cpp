#include "test.hpp"

test::test_base::test_base(const std::string &name) : name(name)
{
}

test::test_base::~test_base()
{
}

const std::string &test::test_base::get_name() const
{
    return this->name;
}

void test::test_base::init()
{
}

void test::test_base::run()
{
}

void test::test_base::dispose()
{
}
