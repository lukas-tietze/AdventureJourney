#include "Objects.hpp"

int offsetX;
int offsetY;
int strideX;
int strideY;
int charWidth;
int charHeight;
int width;
int height;
BitMapFontContent content;
std::string customCharList;

void glutil::BitMapFontInfo::Load(const std::string &path)
{
    json::Node *n;
    json::Parser p;

    p.parse(path, n);
    this->Deserialize(n);
}

json::Node *glutil::BitMapFontInfo::Serialize()
{
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
    if (obj->TryGetAs<json::PrimitiveNode>("width", valueNode, json::ValueType::Number))
        this->width = valueNode->GetValueAsNumber();
    if (obj->TryGetAs<json::PrimitiveNode>("height", valueNode, json::ValueType::Number))
        this->height = valueNode->GetValueAsNumber();
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
        else if (value == "Custom" && obj->TryGetAs<json::PrimitiveNode>("charList", valueNode, json::ValueType::String))
        {
            this->content = BitMapFontContent::Custom;
            this->charList = valueNode->GetValueAsString();
        }
    }
}