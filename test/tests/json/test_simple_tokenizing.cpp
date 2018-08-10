#include <cstdio>

#include "test.hpp"
#include "json.hpp"

int test::json::test_simple_tokenizing()
{
    std::printf("Testing simple tokenizing:\n");

    std::string text = "{"
                       "\"foo\": 3"
                       "}";

    ::json::node *n;
    ::json::parser parser;
    parser.parse(text, &n);

    assert::are_equal(::json::value_type::Object, n->get_type());
    assert::is_not_null(dynamic_cast<::json::object_node *>(n));

    util::printp(n);

    delete n;

    return 0;
}