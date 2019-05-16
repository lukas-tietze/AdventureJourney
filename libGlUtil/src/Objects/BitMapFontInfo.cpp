#include "Objects.hpp"
#include "data/String.hpp"

json::Node *glutil::BitMapFontInfo::Serialize()
{
    auto node = new json::ObjectNode();

    node->Put("offsetX", new json::PrimitiveNode(this->offsetX));
    node->Put("offsetY", new json::PrimitiveNode(this->offsetY));
    node->Put("strideX", new json::PrimitiveNode(this->strideX));
    node->Put("strideY", new json::PrimitiveNode(this->strideY));
    node->Put("charWidth", new json::PrimitiveNode(this->charWidth));
    node->Put("charHeight", new json::PrimitiveNode(this->charHeight));
    node->Put("cols", new json::PrimitiveNode(this->cols));
    node->Put("rows", new json::PrimitiveNode(this->rows));
    node->Put("source", new json::PrimitiveNode(this->source));
    node->Put("content", new json::PrimitiveNode(util::ToString(this->content)));
    node->Put("customCharList", new json::PrimitiveNode(this->content == BitMapFontContent::Custom
                                                            ? this->charList
                                                            : ""));

    return node;
}

void glutil::BitMapFontInfo::Deserialize(const json::Node *node)
{
    const json::ObjectNode *obj;
    json::PrimitiveNode *valueNode;

    if (node == nullptr ||
        node->GetType() != json::ValueType::Object ||
        (obj = dynamic_cast<const json::ObjectNode *>(node)) == nullptr)
        return;

    if (obj->TryGetAs<json::PrimitiveNode>("offsetX", valueNode, json::ValueType::Number))
        this->offsetX = valueNode->GetValueAsNumber();
    if (obj->TryGetAs<json::PrimitiveNode>("offsetY", valueNode, json::ValueType::Number))
        this->offsetY = valueNode->GetValueAsNumber();
    if (obj->TryGetAs<json::PrimitiveNode>("strideX", valueNode, json::ValueType::Number))
        this->strideX = valueNode->GetValueAsNumber();
    if (obj->TryGetAs<json::PrimitiveNode>("strideY", valueNode, json::ValueType::Number))
        this->strideY = valueNode->GetValueAsNumber();
    if (obj->TryGetAs<json::PrimitiveNode>("charWidth", valueNode, json::ValueType::Number))
        this->charWidth = valueNode->GetValueAsNumber();
    if (obj->TryGetAs<json::PrimitiveNode>("charHeight", valueNode, json::ValueType::Number))
        this->charHeight = valueNode->GetValueAsNumber();
    if (obj->TryGetAs<json::PrimitiveNode>("cols", valueNode, json::ValueType::Number))
        this->cols = valueNode->GetValueAsNumber();
    if (obj->TryGetAs<json::PrimitiveNode>("rows", valueNode, json::ValueType::Number))
        this->rows = valueNode->GetValueAsNumber();
    if (obj->TryGetAs<json::PrimitiveNode>("src", valueNode, json::ValueType::String))
        this->source = valueNode->GetValueAsString();
    if (obj->TryGetAs<json::PrimitiveNode>("content", valueNode, json::ValueType::String))
    {
        auto value = valueNode->GetValueAsString();

        if (value == "AZaz09Space")
        {
            this->content = BitMapFontContent::AZaz09Space;
            this->charList = "ABZDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ";
        }
        else if (value == "Ascii32To126")
        {
            this->content = BitMapFontContent::Ascii32To126;
            this->charList = " !\"#$%&'()*+,-./0123456789:;<=>\?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
        }
        else if (value == "Custom" && obj->TryGetAs<json::PrimitiveNode>("customCharList", valueNode, json::ValueType::String))
        {
            this->content = BitMapFontContent::Custom;
            this->charList = valueNode->GetValueAsString();
        }
    }
}