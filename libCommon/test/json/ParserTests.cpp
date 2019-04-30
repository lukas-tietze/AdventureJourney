#include <cstdio>

#include "Test.hpp"
#include "libCommon/test/TestList.hpp"
#include "data/Json.hpp"

namespace
{
const std::string BaseDir = "common/test/json/";
}

void ParseFile(const std::string &name, json::Node *&node)
{
    json::Parser p;
    std::string text;

    assert::IsTrue(util::TryReadFile(BaseDir + name, text), "Failed to load file!");
    p.parse(text, node);
}

void VerifyStructure(json::Node *n)
{
    assert::IsNotNull(n);
    assert::AreEqual(json::ValueType::Object, n->GetType());
    assert::Is<json::ObjectNode>(n);

    json::ObjectNode *obj = static_cast<json::ObjectNode *>(n);

    assert::AreEqual(7, obj->GetChildCount());

    assert::IsTrue(obj->HasChild("number"));
    json::Node *vNumber = obj->Get("number");
    assert::Is<json::PrimitiveNode>(vNumber);
    assert::AreEqual(json::ValueType::Number, vNumber->GetType());
    assert::AreEqual(3.0, static_cast<json::PrimitiveNode *>(vNumber)->GetValueAsNumber());

    assert::IsTrue(obj->HasChild("string"));
    json::Node *vString = obj->Get("string");
    assert::Is<json::PrimitiveNode>(vString);
    assert::AreEqual(json::ValueType::String, vString->GetType());
    assert::AreEqual(std::string("some string"), static_cast<json::PrimitiveNode *>(vString)->GetValueAsString());

    assert::IsTrue(obj->HasChild("true"));
    json::Node *vTrue = obj->Get("true");
    assert::Is<json::PrimitiveNode>(vTrue);
    assert::AreEqual(json::ValueType::True, vTrue->GetType());
    assert::AreEqual(true, static_cast<json::PrimitiveNode *>(vTrue)->GetValueAsBool());

    assert::IsTrue(obj->HasChild("false"));
    json::Node *vFalse = obj->Get("false");
    assert::Is<json::PrimitiveNode>(vFalse);
    assert::AreEqual(json::ValueType::False, vFalse->GetType());
    assert::AreEqual(false, static_cast<json::PrimitiveNode *>(vFalse)->GetValueAsBool());

    assert::IsTrue(obj->HasChild("null"));
    json::Node *vNull = obj->Get("null");
    assert::Is<json::PrimitiveNode>(vNull);
    assert::AreEqual(json::ValueType::Null, vNull->GetType());
    assert::IsTrue(static_cast<json::PrimitiveNode *>(vNull)->IsValueNull());

    assert::IsTrue(obj->HasChild("array"));
    assert::Is<json::ArrayNode>(obj->Get("array"));
    json::ArrayNode *vArray = static_cast<json::ArrayNode *>(obj->Get("array"));
    assert::AreEqual(json::ValueType::Array, vArray->GetType());
    assert::AreEqual(7, vArray->GetChildCount());

    assert::AreEqual(json::ValueType::Number, vArray->Get(0)->GetType());
    assert::AreEqual(json::ValueType::True, vArray->Get(1)->GetType());
    assert::AreEqual(json::ValueType::False, vArray->Get(2)->GetType());
    assert::AreEqual(json::ValueType::Null, vArray->Get(3)->GetType());
    assert::AreEqual(json::ValueType::String, vArray->Get(4)->GetType());
    assert::AreEqual(json::ValueType::Object, vArray->Get(5)->GetType());
    assert::AreEqual(json::ValueType::Array, vArray->Get(6)->GetType());

    assert::IsTrue(obj->HasChild("object"));
    assert::Is<json::ArrayNode>(obj->Get("object"));
    json::ObjectNode *vObject = static_cast<json::ObjectNode *>(obj->Get("object"));
    assert::AreEqual(json::ValueType::Object, vObject->GetType());
    assert::AreEqual(3, vObject->GetChildCount());

    assert::IsTrue(vObject->HasChild("prop1"));
    assert::AreEqual(json::ValueType::Number, vObject->Get("prop1")->GetType());
    assert::IsTrue(vObject->HasChild("prop2"));
    assert::AreEqual(json::ValueType::String, vObject->Get("prop2")->GetType());
    assert::IsTrue(vObject->HasChild("prop3"));
    assert::AreEqual(json::ValueType::String, vObject->Get("prop3")->GetType());
}

json::Node *CreateTestNode()
{
    auto n = new json::ObjectNode();

    n->Put("number", 3.0);
    n->Put("string", "some string");
    n->Put("false", false);
    n->Put("true", true);
    n->PutNull("null");

    auto array = new json::ArrayNode();
    array->Put(1.0);
    array->Put(true);
    array->Put(false);
    array->PutNull();
    array->Put("three");

    auto subObject = new json::ObjectNode();
    subObject->PutNull("dummy");

    array->Put(subObject);

    auto subArray = new json::ArrayNode();
    subArray->Put(1.0);
    subArray->Put(2.0);
    subArray->Put(3.0);

    array->Put(subArray);
    n->Put("array", array);

    subObject = new json::ObjectNode();
    subObject->Put("prop1", 1.0);
    subObject->Put("prop2", "prop_two");
    subObject->Put("prop3", "prop_three");

    n->Put("object", subObject);

    return n;
}

int test::jsonTest::ExpandedRead()
{
    json::Node *n = nullptr;

    ParseFile("expanded.json", n);
    VerifyStructure(n);

    return 0;
}

int test::jsonTest::CompactRead()
{
    json::Node *n = nullptr;

    ParseFile("compact.json", n);
    VerifyStructure(n);

    return 0;
}

int test::jsonTest::ExpandedWrite()
{
    json::Node *n = CreateTestNode();
    json::FormattedPrinter p;
    std::string text;

    n->PrintFormatted(p);

    assert::IsTrue(util::TryReadFile(BaseDir + "expanded.json", text));
    assert::IsNotNull(n);
    assert::AreEqual(text, p.ToString());

    return 0;
}

int test::jsonTest::CompactWrite()
{
    json::Node *n = CreateTestNode();
    json::FormattedPrinter p;
    std::string text;

    p.SetCompactStyle(true);

    n->PrintFormatted(p);

    assert::IsTrue(util::TryReadFile(BaseDir + "compact.json", text));
    assert::IsNotNull(n);
    assert::AreEqual(text, p.ToString());

    return 0;
}

int test::jsonTest::Integrity()
{
    VerifyStructure(CreateTestNode());

    return 0;
}

int test::jsonTest::WriteRead()
{
    //TODO!
    // auto n = CreateTestNode();

    return 0;
}

int test::jsonTest::ReadWrite()
{
    //TODO!

    return 0;
}