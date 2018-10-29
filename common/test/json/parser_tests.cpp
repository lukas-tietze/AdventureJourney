#include <cstdio>

#include "test.hpp"
#include "../test_list.hpp"
#include "data/json.hpp"

void parse_file(const std::string &name, json::node *&node)
{
    json::parser p;
    std::string text;

    assert::is_true(util::try_read_file("test/tests/json/" + name, text));
    p.parse(text, node);
}

void verify_structure(json::node *n)
{
    assert::is_not_null(n);
    assert::are_equal(json::value_type::Object, n->get_type());
    assert::is<json::object_node>(n);

    json::object_node *obj = static_cast<json::object_node *>(n);

    assert::are_equal(7, obj->get_child_count());

    assert::is_true(obj->has_child("number"));
    json::node *vNumber = obj->get("number");
    assert::is<json::primitive_node>(vNumber);
    assert::are_equal(json::value_type::Number, vNumber->get_type());
    assert::are_equal(3.0, static_cast<json::primitive_node *>(vNumber)->get_value_as_number());

    assert::is_true(obj->has_child("string"));
    json::node *vString = obj->get("string");
    assert::is<json::primitive_node>(vString);
    assert::are_equal(json::value_type::String, vString->get_type());
    assert::are_equal(std::string("some string"), static_cast<json::primitive_node *>(vString)->get_value_as_string());

    assert::is_true(obj->has_child("true"));
    json::node *vTrue = obj->get("true");
    assert::is<json::primitive_node>(vTrue);
    assert::are_equal(json::value_type::True, vTrue->get_type());
    assert::are_equal(true, static_cast<json::primitive_node *>(vTrue)->get_value_as_bool());

    assert::is_true(obj->has_child("false"));
    json::node *vFalse = obj->get("false");
    assert::is<json::primitive_node>(vFalse);
    assert::are_equal(json::value_type::False, vFalse->get_type());
    assert::are_equal(false, static_cast<json::primitive_node *>(vFalse)->get_value_as_bool());

    assert::is_true(obj->has_child("null"));
    json::node *vNull = obj->get("null");
    assert::is<json::primitive_node>(vNull);
    assert::are_equal(json::value_type::Null, vNull->get_type());
    assert::is_true(static_cast<json::primitive_node *>(vNull)->is_value_null());

    assert::is_true(obj->has_child("array"));
    assert::is<json::array_node>(obj->get("array"));
    json::array_node *vArray = static_cast<json::array_node *>(obj->get("array"));
    assert::are_equal(json::value_type::Array, vArray->get_type());
    assert::are_equal(7, vArray->get_child_count());

    assert::are_equal(json::value_type::Number, vArray->get(0)->get_type());
    assert::are_equal(json::value_type::True, vArray->get(1)->get_type());
    assert::are_equal(json::value_type::False, vArray->get(2)->get_type());
    assert::are_equal(json::value_type::Null, vArray->get(3)->get_type());
    assert::are_equal(json::value_type::String, vArray->get(4)->get_type());
    assert::are_equal(json::value_type::Object, vArray->get(5)->get_type());
    assert::are_equal(json::value_type::Array, vArray->get(6)->get_type());

    assert::is_true(obj->has_child("object"));
    assert::is<json::array_node>(obj->get("object"));
    json::object_node *vObject = static_cast<json::object_node *>(obj->get("object"));
    assert::are_equal(json::value_type::Object, vObject->get_type());
    assert::are_equal(3, vObject->get_child_count());

    assert::is_true(vObject->has_child("prop1"));
    assert::are_equal(json::value_type::Number, vObject->get("prop1")->get_type());
    assert::is_true(vObject->has_child("prop2"));
    assert::are_equal(json::value_type::String, vObject->get("prop2")->get_type());
    assert::is_true(vObject->has_child("prop3"));
    assert::are_equal(json::value_type::String, vObject->get("prop3")->get_type());
}

json::node *create_test_node()
{
    auto n = new json::object_node();

    n->put("number", 3.0);
    n->put("string", "some string");
    n->put("false", false);
    n->put("true", true);
    n->put_null("null");

    auto array = new json::array_node();
    array->put(1.0);
    array->put(true);
    array->put(false);
    array->put_null();
    array->put("three");

    auto subObject = new json::object_node();
    subObject->put_null("dummy");

    array->put(subObject);

    auto subArray = new json::array_node();
    subArray->put(1.0);
    subArray->put(2.0);
    subArray->put(3.0);

    array->put(subArray);
    n->put("array", array);

    subObject = new json::object_node();
    subObject->put("prop1", 1.0);
    subObject->put("prop2", "prop_two");
    subObject->put("prop3", "prop_three");

    n->put("object", subObject);

    return n;
}

int test::json_test::expanded_read()
{
    json::node *n = nullptr;

    parse_file("expanded.json", n);
    verify_structure(n);

    return 0;
}

int test::json_test::compact_read()
{
    json::node *n = nullptr;

    parse_file("compact.json", n);
    verify_structure(n);

    return 0;
}

int test::json_test::expanded_write()
{
    json::node *n = create_test_node();
    json::formatted_printer p;
    std::string text;

    n->print_formatted(p);

    assert::is_true(util::try_read_file("test/tests/json/expanded.json", text));
    assert::is_not_null(n);
    assert::are_equal(text, p.to_string());

    return 0;
}

int test::json_test::compact_write()
{
    json::node *n = create_test_node();
    json::formatted_printer p;
    std::string text;

    p.set_compact_style(true);

    n->print_formatted(p);

    assert::is_true(util::try_read_file("test/tests/json/compact.json", text));
    assert::is_not_null(n);
    assert::are_equal(text, p.to_string());

    return 0;
}

int test::json_test::integrity()
{
    verify_structure(create_test_node());

    return 0;
}

int test::json_test::write_read()
{
    //TODO!
    // auto n = create_test_node();

    return 0;
}

int test::json_test::read_write()
{
    //TODO!

    return 0;
}