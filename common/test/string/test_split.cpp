#include "test.hpp"
#include "../test_list.hpp"
#include "data/string.hpp"

int test::string_test::split_space()
{
    std::vector<std::string> parts;

    parts = util::split(" a\tb 1c2\n3   ##", true);

    assert::are_equal((size_t)3, parts.size());
    assert::are_equal(std::string("a\tb"), parts[0]);
    assert::are_equal(std::string("1c2\n3"), parts[1]);
    assert::are_equal(std::string("##"), parts[2]);

    return 0;
}

int test::string_test::split_custom_char()
{
    std::vector<std::string> parts;

    // parts = util::split("__ab__cd ef_gh____", '_');

    parts = util::split("__ab_cd ef_gh_ ___", '_', true);

    assert::are_equal((size_t)4, parts.size());
    assert::are_equal(std::string("ab"), parts[0]);
    assert::are_equal(std::string("cd ef"), parts[1]);
    assert::are_equal(std::string("gh"), parts[2]);
    assert::are_equal(std::string(" "), parts[3]);

    return 0;
}

int test::string_test::split_multiple_chars()
{
    auto parts = util::split(" ,ab cd_ef,gh_  ,ij", " ,_");

    return 0;
}

int test::string_test::split_function()
{
    return 0;
}
