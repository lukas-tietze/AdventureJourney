#include <cstdio>

#include "test.hpp"
#include "data/json.hpp"

int test::json_test::test_simple_tokenizing()
{
    std::string text;
    json::tokenizer t;
    json::parser p;
    json::node *n;

    assert::is_true(util::try_read_file("test/tests/json/simple_test.json", text));
    p.parse(text, n);

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

    return 0;
}