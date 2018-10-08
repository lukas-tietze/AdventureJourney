#include "test.hpp"
#include "data/string.hpp"

int test::string_test::strip()
{
    assert::are_equal(std::string("abc"), util::strip(" abc"));
    assert::are_equal(std::string("abc"), util::strip(" abc "));
    assert::are_equal(std::string("abc"), util::strip("   abc    "));
    assert::are_equal(std::string("abc"), util::strip(" \t\nabc\n\n   \t"));

    return 0;
}

int test::string_test::strip_front()
{
    assert::are_equal(std::string("abc "), util::strip_front(" abc "));
    assert::are_equal(std::string("abc    "), util::strip_front("   abc    "));
    assert::are_equal(std::string("abc\n\n   \t"), util::strip_front(" \t\nabc\n\n   \t"));

    return 0;
}

int test::string_test::strip_back()
{
    assert::are_equal(std::string(" abc"), util::strip_back(" abc "));
    assert::are_equal(std::string("   abc"), util::strip_back("   abc    "));
    assert::are_equal(std::string(" \t\nabc"), util::strip_back(" \t\nabc\n\n   \t"));

    return 0;
}