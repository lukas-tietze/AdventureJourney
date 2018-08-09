#include "test.hpp"
#include "json.hpp"

#include <cstdio>

test::test_result test::json::test_simple_tokenizing()
{
    std::string text = "{"
                       "\"foo\": 3"
                       "}";

    ::json::node *n;
    ::json::parser parser;
    parser.parse(text, &n);

    test::test_result res;
    return res;
}