#include "data/json.hpp"

#include "test.hpp"

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

    return 0;
}