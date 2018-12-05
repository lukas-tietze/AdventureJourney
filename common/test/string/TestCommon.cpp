#include "Test.hpp"
#include "common/test/TestList.hpp"
#include "data/String.hpp"

int test::stringTest::Format()
{
    return 0;
}

int test::stringTest::ToUpper()
{
    assert::AreEqual(std::string("ABC"), util::ToUpper("abC"));
    assert::AreEqual(std::string("123A"), util::ToUpper("123a"));
    assert::AreEqual(std::string("A_B_2_C"), util::ToUpper("a_B_2_c"));

    std::string refString;

    refString = "abC";
    util::ToUpperInplace(refString);
    assert::AreEqual(std::string("ABC"), refString);

    refString = "123a";
    util::ToUpperInplace(refString);
    assert::AreEqual(std::string("123A"), refString);

    refString = "a_B_2_c";
    util::ToUpperInplace(refString);
    assert::AreEqual(std::string("A_B_2_C"), refString);

    return 0;
}

int test::stringTest::ToLower()
{
    assert::AreEqual(std::string("abc"), util::ToLower("abC"));
    assert::AreEqual(std::string("123a"), util::ToLower("123A"));
    assert::AreEqual(std::string("a_b_2_c"), util::ToLower("a_B_2_c"));

    std::string refString;

    refString = "abC";
    util::ToLowerInplace(refString);
    assert::AreEqual(std::string("abc"), refString);

    refString = "123A";
    util::ToLowerInplace(refString);
    assert::AreEqual(std::string("123a"), refString);

    refString = "a_B_2_c";
    util::ToLowerInplace(refString);
    assert::AreEqual(std::string("a_b_2_c"), refString);

    return 0;
}
