#include "test.hpp"
#include "data/string.hpp"

int test::string_test::format()
{
    return 0;
}

int test::string_test::to_upper()
{
    assert::are_equal(std::string("ABC"), util::to_upper("abC"));
    assert::are_equal(std::string("123A"), util::to_upper("123a"));
    assert::are_equal(std::string("A_B_2_C"), util::to_upper("a_B_2_c"));

    std::string refString;

    refString = "abC";
    util::to_upper_inplace(refString);
    assert::are_equal(std::string("ABC"), refString);

    refString = "123a";
    util::to_upper_inplace(refString);
    assert::are_equal(std::string("123A"), refString);

    refString = "a_B_2_c";
    util::to_upper_inplace(refString);
    assert::are_equal(std::string("A_B_2_C"), refString);

    return 0;
}

int test::string_test::to_lower()
{
    assert::are_equal(std::string("abc"), util::to_lower("abC"));
    assert::are_equal(std::string("123a"), util::to_lower("123A"));
    assert::are_equal(std::string("a_b_2_c"), util::to_lower("a_B_2_c"));

    std::string refString;

    refString = "abC";
    util::to_lower_inplace(refString);
    assert::are_equal(std::string("abc"), refString);

    refString = "123A";
    util::to_lower_inplace(refString);
    assert::are_equal(std::string("123a"), refString);

    refString = "a_B_2_c";
    util::to_lower_inplace(refString);
    assert::are_equal(std::string("a_b_2_c"), refString);

    return 0;
}

