#include "View.hpp"

terminal::ColorPallette::ColorPallette() : ColorPallette(COLORS, COLOR_PAIRS)
{
}

terminal::ColorPallette::ColorPallette(size_t colors, size_t colorPairs) : colors(colors),
                                                                           colorPairs(colorPairs)
{
}

terminal::ColorPallette::ColorPallette(const util::Array<util::Color> &colors, const util::Array<ColorPair> &colorPairs) : colors(colors),
                                                                                                                           colorPairs(colorPairs)
{
}

const util::Array<util::Color> &terminal::ColorPallette::GetColors() const
{
    return this->colors;
}

const util::Array<terminal::ColorPair> &terminal::ColorPallette::GetColorPairs() const
{
    return this->colorPairs;
}

util::Array<util::Color> &terminal::ColorPallette::GetColors()
{
    return this->colors;
}

util::Array<terminal::ColorPair> &terminal::ColorPallette::GetColorPairs()
{
    return this->colorPairs;
}

size_t terminal::ColorPallette::GetColorCount() const
{
    return this->colors.Length();
}

size_t terminal::ColorPallette::GetColorPairCount() const
{
    return this->colorPairs.Length();
}

bool terminal::ColorPallette::IsCompatible(size_t colors, size_t colorPairs) const
{
    return this->colors.Length() <= colors && this->colorPairs.Length() <= colorPairs;
}

bool terminal::ColorPallette::Matches(size_t colors, size_t colorPairs) const
{
    return this->colors.Length() == colors && this->colorPairs.Length() == colorPairs;
}

json::Node *terminal::ColorPallette::Serialize()
{
    auto colors = new json::ArrayNode();

    for (auto pos = this->colors.begin(), end = this->colors.end(); pos != end; ++pos)
    {
        colors->Put(new json::PrimitiveNode(pos->AsHex4String()));
    }

    auto colorPairs = new json::ArrayNode();

    for (auto pos = this->colorPairs.begin(), end = this->colorPairs.end(); pos != end; ++pos)
    {
        auto pair = new json::ObjectNode();

        pair->Put("fg", new json::PrimitiveNode(std::get<0>(*pos)));
        pair->Put("bg", new json::PrimitiveNode(std::get<1>(*pos)));
        colorPairs->Put(pair);
    }

    auto object = new json::ObjectNode();

    object->Put("colors", colors);
    object->Put("colorPairs", colorPairs);

    return object;
}

void terminal::ColorPallette::Deserialize(const json::Node *root)
{
    if (root->GetType() != json::ValueType::Object)
    {
        throw util::Exception("Failed to deserialize ColorPallette: Illegal type of root");
    }

    auto objRoot = dynamic_cast<const json::ObjectNode *>(root);
    json::Node *buf;
    const json::ArrayNode *array;
    const json::PrimitiveNode *item;
    const json::ObjectNode *obj;

    size_t i = 0;

    if (objRoot->TryGet("colors", buf) &&
        array->GetType() == json::ValueType::Array &&
        (array = dynamic_cast<const json::ArrayNode *>(buf)) != nullptr)
    {
        for (auto pos = array->begin(), end = array->end(); pos != end; pos++)
        {
            if ((*pos)->GetType() == json::ValueType::String &&
                (item = dynamic_cast<const json::PrimitiveNode *>(*pos)) != nullptr)
            {
                this->colors[i++] = util::Color::FromHexString(item->GetValueAsString());
            }
        }
    }

    i = 0;

    if (objRoot->TryGet("colorPairs", buf) &&
        array->GetType() == json::ValueType::Array &&
        (array = dynamic_cast<const json::ArrayNode *>(buf)) != nullptr)
    {
        for (auto pos = array->begin(), end = array->end(); pos != end; pos++)
        {
            if ((*pos)->GetType() == json::ValueType::Object &&
                (obj = dynamic_cast<const json::ObjectNode *>(*pos)) != nullptr)
            {
                colorId_t fg = 0;
                colorId_t bg = 0;

                if (obj->TryGet("fg", buf) &&
                    buf->GetType() == json::ValueType::Number &&
                    (item = dynamic_cast<const json::PrimitiveNode *>(buf)) != nullptr)
                {
                    fg = static_cast<colorId_t>(item->GetValueAsNumber());
                }

                if (obj->TryGet("bg", buf) &&
                    buf->GetType() == json::ValueType::Number &&
                    (item = dynamic_cast<const json::PrimitiveNode *>(buf)) != nullptr)
                {
                    bg = static_cast<colorId_t>(item->GetValueAsNumber());
                }

                this->colorPairs[i++] = std::make_tuple(fg, bg);
            }
        }
    }
}