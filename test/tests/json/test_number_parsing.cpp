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

namespace
{
    void test_dummy()
    {
        parse_number("4.0E2");
    }
}

int test::json_test::number_parsing()
{
    test_dummy();

    assert::are_equal(1.0, parse_number("1.0"), CPL_LOCATION);
    assert::are_equal(1.0, parse_number("1"), CPL_LOCATION);
    assert::are_equal(0.5, parse_number("0.5"), CPL_LOCATION);
    assert::are_equal(3.5, parse_number("3.5"), CPL_LOCATION);

    assert::are_equal(-1.0, parse_number("-1.0"), CPL_LOCATION);
    assert::are_equal(-1.0, parse_number("-1"), CPL_LOCATION);
    assert::are_equal(-0.5, parse_number("-0.5"), CPL_LOCATION);
    assert::are_equal(-3.5, parse_number("-3.5"), CPL_LOCATION);

    assert::are_equal(400.0, parse_number("4e2"), CPL_LOCATION);
    assert::are_equal(400.0, parse_number("4.0e2"), CPL_LOCATION);
    assert::are_equal(40.0, parse_number("0.4e2"), CPL_LOCATION);

    assert::are_equal(400.0, parse_number("4E2"), CPL_LOCATION);
    assert::are_equal(400.0, parse_number("4.0E2"), CPL_LOCATION);
    assert::are_equal(40.0, parse_number("0.4E2"), CPL_LOCATION);

    return 0;
}