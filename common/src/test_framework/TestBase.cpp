#include "Test.hpp"

test::TestBase::TestBase(const std::string &name) : name(name)
{
}

test::TestBase::~TestBase()
{
}

const std::string &test::TestBase::GetName() const
{
    return this->name;
}

void test::TestBase::Init()
{
}

void test::TestBase::Run()
{
}

void test::TestBase::Dispose()
{
}
