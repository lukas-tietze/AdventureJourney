#include <vector>

#include "test.hpp"

int main(int argc, char **argv)
{
    test::test_collection tests;

    tests.push_back(test::test_run(new test::simple_test("simple tokenizing", &test::json::test_simple_tokenizing)));
    tests.push_back(test::test_run(new test::simple_test("complex tokenizing", &test::json::test_complex_tokenizing)));

    for(auto &testRun : tests)
    {
        testRun.execute();
        util::printf(testRun);
    }

    return 0;
}