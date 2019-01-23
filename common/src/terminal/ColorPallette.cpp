#include "terminal/TerminalView.hpp"

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

namespace
{
terminal::ColorPallette default2;
bool default2Initialized = false;

terminal::ColorPallette default8;
bool default8Initialized = false;

terminal::ColorPallette default16;
bool default16Initialized = false;

terminal::ColorPallette default88;
bool default88Initialized = false;

terminal::ColorPallette default256;
bool default256Initialized = false;

} // namespace

const terminal::ColorPallette &terminal::ColorPallette::GetDefault2()
{
    if (!default2Initialized)
    {
        default2 = ColorPallette(2, 2);
        auto &c = default2.colors;
        auto &p = default2.colorPairs;

        c[0] = util::colors::Black;
        c[1] = util::colors::White;
        p[0] = std::make_tuple(0, 1);
        p[1] = std::make_tuple(1, 0);
    }

    return default2;
}

const terminal::ColorPallette &terminal::ColorPallette::GetDefault8()
{
    if (!default8Initialized)
    {
        default2 = ColorPallette(8, 8);
        auto &c = default2.colors;
        auto &p = default2.colorPairs;

        c[0] = util::colors::Black;
        c[1] = util::colors::White;
        c[2] = util::colors::Red;
        c[3] = util::colors::Green;
        c[4] = util::colors::Blue;
        c[5] = util::colors::DarkRed;
        c[6] = util::colors::DarkGreen;
        c[7] = util::colors::DarkBlue;

        p[0] = std::make_tuple(0, 1);
        p[1] = std::make_tuple(1, 0);
        p[0] = std::make_tuple(0, 1);
        p[0] = std::make_tuple(0, 1);
        p[0] = std::make_tuple(0, 1);
        p[0] = std::make_tuple(0, 1);
        p[0] = std::make_tuple(0, 1);
        p[0] = std::make_tuple(0, 1);
    }

    return default8;
}

const terminal::ColorPallette &terminal::ColorPallette::GetDefault16()
{
    if (!default16Initialized)
    {
    }

    return default16;
}

const terminal::ColorPallette &terminal::ColorPallette::GetDefault88()
{
    if (!default88Initialized)
    {
    }

    return default88;
}

const terminal::ColorPallette &terminal::ColorPallette::GetDefault256()
{
    if (!default256Initialized)
    {
    }

    return default256;
}
