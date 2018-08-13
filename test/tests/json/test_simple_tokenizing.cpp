#include <cstdio>

#include "test.hpp"
#include "json.hpp"

int test::json::test_simple_tokenizing()
{
    std::string text;
    ::json::tokenizer t;
    ::json::parser p;
    ::json::node *n;

    assert::is_true(util::try_read_file("test/tests/json/simple_test.json", text));
    p.parse(text, &n);

    return 0;
}