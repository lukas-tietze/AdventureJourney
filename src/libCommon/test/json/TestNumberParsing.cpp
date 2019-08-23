#include "Test.hpp"
#include "libCommon/test/TestList.hpp"
#include "data/Json.hpp"

double ParseNumber(const std::string &s)
{
    std::string data = "{\"x\":" + s + "}";
    json::Node *n;
    json::Parser p;

    p.parse(data, n);

    auto obj = dynamic_cast<const json::ObjectNode *>(n);

    assert::IsNotNull(obj);

    auto node = dynamic_cast<const json::PrimitiveNode *>(obj->Get("x"));

    assert::IsNotNull(node);
    assert::AreEqual(json::ValueType::Number, node->GetType());

    return node->GetValueAsNumber();
}

namespace
{
    void test_dummy()
    {
        ParseNumber("4.0E2");
    }
}

int test::jsonTest::NumberParsing()
{
    test_dummy();

    assert::AreEqual(1.0, ParseNumber("1.0"));
    assert::AreEqual(1.0, ParseNumber("1"));
    assert::AreEqual(0.5, ParseNumber("0.5"));
    assert::AreEqual(3.5, ParseNumber("3.5"));

    assert::AreEqual(-1.0, ParseNumber("-1.0"));
    assert::AreEqual(-1.0, ParseNumber("-1"));
    assert::AreEqual(-0.5, ParseNumber("-0.5"));
    assert::AreEqual(-3.5, ParseNumber("-3.5"));

    assert::AreEqual(400.0, ParseNumber("4e2"));
    assert::AreEqual(400.0, ParseNumber("4.0e2"));
    assert::AreEqual(40.0, ParseNumber("0.4e2"));

    assert::AreEqual(400.0, ParseNumber("4E2"));
    assert::AreEqual(400.0, ParseNumber("4.0E2"));
    assert::AreEqual(40.0, ParseNumber("0.4E2"));

    return 0;
}