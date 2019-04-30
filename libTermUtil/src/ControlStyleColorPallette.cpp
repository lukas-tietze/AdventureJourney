#include "terminal/View.hpp"
#include "data/String.hpp"
#include "data/EnumHelper.hpp"

terminal::ControlStyleColorPallette::ControlStyleColorPallette() : ColorPallette()
{
}

terminal::ControlStyleColorPallette::ControlStyleColorPallette(const util::Array<util::Color> &colors, const util::Array<ColorPair> &colorPairs) : ColorPallette(colors, colorPairs)
{
}

terminal::ControlStyleColorPallette::ControlStyleColorPallette(const util::Array<util::Color> &colors, const util::Array<ColorPair> &colorPairs, const std::array<colorId_t, static_cast<size_t>(ControlStyleColor::ClearColor) + 1> &styles) : ColorPallette(colors, colorPairs),
                                                                                                                                                                                                                                                styles(styles)
{
}

terminal::colorId_t terminal::ControlStyleColorPallette::operator[](ControlStyleColor styleId) const
{
    return this->styles[static_cast<size_t>(styleId)];
}

terminal::colorId_t &terminal::ControlStyleColorPallette::operator[](ControlStyleColor styleId)
{
    return this->styles[static_cast<size_t>(styleId)];
}

terminal::colorId_t terminal::ControlStyleColorPallette::GetStyle(ControlStyleColor styleId) const
{
    return this->styles[static_cast<size_t>(styleId)];
}

void terminal::ControlStyleColorPallette::SetStyle(ControlStyleColor styleId, colorId_t value)
{
    this->styles[static_cast<size_t>(styleId)] = value;
}

std::array<terminal::colorId_t, static_cast<int>(terminal::ControlStyleColor::ClearColor) + 1> &terminal::ControlStyleColorPallette::GetControlColors()
{
    return this->styles;
}

const std::array<terminal::colorId_t, static_cast<int>(terminal::ControlStyleColor::ClearColor) + 1> &terminal::ControlStyleColorPallette::GetControlColors() const
{
    return this->styles;
}

json::Node *terminal::ControlStyleColorPallette::Serialize()
{
    auto node = this->terminal::ColorPallette::Serialize();

    if (node != nullptr)
    {
        auto obj = dynamic_cast<json::ObjectNode *>(node);

        if (obj != nullptr)
        {
            for (size_t i = 0, end = static_cast<size_t>(terminal::ControlStyleColor::ClearColor) + 1; i < end; i++)
            {
                obj->Put(util::ToString(static_cast<terminal::ControlStyleColor>(i)), this->styles[i]);
            }
        }
    }

    return node;
}

void terminal::ControlStyleColorPallette::Deserialize(const json::Node *node)
{
    this->ColorPallette::Deserialize(node);

    const json::ObjectNode *obj;
    const json::PrimitiveNode *prim;

    if (json::AssureType<json::ObjectNode>(node, obj, json::ValueType::Object))
    {
        for (const auto &value : *obj)
        {
            if (json::AssureType<json::PrimitiveNode>(value.second, prim, json::ValueType::Number))
            {
                auto id = util::Deserialize<terminal::ControlStyleColor>(value.first);
                auto style = static_cast<colorPairId_t>(prim->GetValueAsNumber());
            }
        }
    }
}
