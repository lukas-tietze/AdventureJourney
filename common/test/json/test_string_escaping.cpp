#include "test.hpp"
#include "../test_list.hpp"
#include "data/json.hpp"

const std::string parse_string(const std::string &s)
{
    std::string data = "{\"x\":\"" + s + "\"}";
    json::node *n;
    json::parser p;

    p.parse(data, n);

    auto obj = dynamic_cast<const json::object_node *>(n);

    assert::is_not_null(obj);

    auto node = dynamic_cast<const json::primitive_node *>(obj->get("x"));

    assert::is_not_null(node);
    assert::are_equal(json::value_type::String, node->get_type());

    return node->get_value_as_string();
}

int test::json_test::string_escaping()
{
    assert::are_equal(std::string("abc"), parse_string("abc"));
    assert::are_equal(std::string("a\\b"), parse_string("a\\\\b"));
    assert::are_equal(std::string("a\"b"), parse_string("a\\\"b"));
    assert::are_equal(std::string("a/b"), parse_string("a\\/b"));
    assert::are_equal(std::string("a\bb"), parse_string("a\\bb"));
    assert::are_equal(std::string("a\fb"), parse_string("a\\fb"));
    assert::are_equal(std::string("a\nb"), parse_string("a\\nb"));
    assert::are_equal(std::string("a\rb"), parse_string("a\\rb"));
    assert::are_equal(std::string("a\tb"), parse_string("a\\tb"));
    
    assert::are_equal(std::string("a\u0000b"), parse_string("a\\u0000nb"));
    assert::are_equal(std::string("a\u0030b"), parse_string("a\\u0030nb"));
    assert::are_equal(std::string("a\u0ab3b"), parse_string("a\\u0ab3nb"));
    assert::are_equal(std::string("a\u2e0cb"), parse_string("a\\u2e0cnb"));
    assert::are_equal(std::string("a\u2300b"), parse_string("a\\u2300nb"));
    assert::are_equal(std::string("a\u0ff0b"), parse_string("a\\u0ff0nb"));

    return 0;
}