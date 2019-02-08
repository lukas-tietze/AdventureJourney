#include "terminal/TerminalView.hpp"
#include "data/String.hpp"

terminal::ControlStyleColorPallette::ControlStyleColorPallette() : ColorPallette()
{
}

terminal::ControlStyleColorPallette::ControlStyleColorPallette(const util::Array<util::Color> &colors, const util::Array<ColorPair> &colorPairs) : ColorPallette(colors, colorPairs)
{
}

terminal::ControlStyleColorPallette::ControlStyleColorPallette(const util::Array<util::Color> &colors, const util::Array<ColorPair> &colorPairs, const std::array<colorId_t, static_cast<size_t>(ControlStyleColor::ColorCount)> &styles) : ColorPallette(colors, colorPairs),
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

std::array<terminal::colorId_t, static_cast<int>(terminal::ControlStyleColor::ColorCount)> &terminal::ControlStyleColorPallette::GetControlColors()
{
    return this->styles;
}

const std::array<terminal::colorId_t, static_cast<int>(terminal::ControlStyleColor::ColorCount)> &terminal::ControlStyleColorPallette::GetControlColors() const
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
            for (size_t i = 0, end = static_cast<size_t>(terminal::ControlStyleColor::ColorCount); i < end; i++)
            {
                obj->Put(util::ToString(static_cast<terminal::ControlStyleColor>(i)), this->styles[i]);
            }
        }
    }

    return node;
}

void terminal::ControlStyleColorPallette::Deserialize(const json::Node *)
{
    // TODO
}
