#include "data/json.hpp"
#include "test.hpp"

const double parse_number(const std::string &s)
{
    std::string data = "{\"x\":" + s + "}";
    json::node *n;
    json::parser p;

    p.parse(data, n);

    auto obj = dynamic_cast<const json::object_node *>(n);

    assert::is_not_null(obj);

    auto node = dynamic_cast<const json::primitive_node *>(obj->get("x"));

    assert::is_not_null(node);
    assert::are_equal(json::value_type::Number, node->get_type());
    
    return node->get_value_as_number();
}

int test::json_test::number_parsing()
{
    assert::are_equal(1.0, parse_number("1.0"));

    return 0;
}