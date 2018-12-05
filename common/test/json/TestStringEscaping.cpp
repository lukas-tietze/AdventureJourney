#include "Test.hpp"
#include "common/test/TestList.hpp"
#include "data/Json.hpp"

const std::string parse_string(const std::string &s)
{
    std::string data = "{\"x\":\"" + s + "\"}";
    json::Node *n;
    json::Parser p;

    p.parse(data, n);

    auto obj = dynamic_cast<const json::ObjectNode *>(n);

    assert::IsNotNull(obj);

    auto node = dynamic_cast<const json::PrimitiveNode *>(obj->Get("x"));

    assert::IsNotNull(node);
    assert::AreEqual(json::ValueType::String, node->GetType());

    return node->GetValueAsString();
}

int test::jsonTest::StringEscaping()
{
    assert::AreEqual(std::string("abc"), parse_string("abc"));
    assert::AreEqual(std::string("a\\b"), parse_string("a\\\\b"));
    assert::AreEqual(std::string("a\"b"), parse_string("a\\\"b"));
    assert::AreEqual(std::string("a/b"), parse_string("a\\/b"));
    assert::AreEqual(std::string("a\bb"), parse_string("a\\bb"));
    assert::AreEqual(std::string("a\fb"), parse_string("a\\fb"));
    assert::AreEqual(std::string("a\nb"), parse_string("a\\nb"));
    assert::AreEqual(std::string("a\rb"), parse_string("a\\rb"));
    assert::AreEqual(std::string("a\tb"), parse_string("a\\tb"));

    assert::AreEqual(std::string("a\u0ab3b"), parse_string("a\\u0ab3b"));
    assert::AreEqual(std::string("a\u2e0cb"), parse_string("a\\u2e0cb"));
    assert::AreEqual(std::string("a\u2300b"), parse_string("a\\u2300b"));
    assert::AreEqual(std::string("a\u0ff0b"), parse_string("a\\u0ff0b"));

    return 0;
}