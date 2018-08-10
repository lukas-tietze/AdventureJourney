#include <vector>

#include "test.hpp"

int main(int argc, char **argv)
{
    test::test_collection tests;

    tests.push_back(test::test_run(new test::simple_test("simple tokenizing", &test::json::test_simple_tokenizing)));

    for(auto &testRun : tests)
    {
        testRun.execute();
        util::printr(testRun);
    }

    return 0;
}