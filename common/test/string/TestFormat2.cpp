#include "Test.hpp"
#include "common/test/TestList.hpp"
#include "data/String.hpp"

int test::stringTest::Format2()
{
    assert::AreEqual(std::string(""), util::Format2(""));
    assert::AreEqual(std::string("%"), util::Format2("\\%"));
    assert::AreEqual(std::string("\\abc12"), util::Format2("\\\\%", "abc12"));
    assert::AreEqual(std::string("123abcd"), util::Format2("1%%%d", 23, 'a', "bc"));

    return 0;
}