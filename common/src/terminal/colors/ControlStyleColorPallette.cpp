#include "terminal/TerminalView.hpp"

terminal::controlStyles::ControlStyleColorPallette::ControlStyleColorPallette(const util::Array<util::Color> &colors, const util::Array<ColorPair> &colorPairs) : ColorPallette(colors, colorPairs)
{
}

terminal::colorPairId_t terminal::controlStyles::ControlStyleColorPallette::GetControlText() const
{
    return this->controlText;
}

terminal::colorPairId_t terminal::controlStyles::ControlStyleColorPallette::GetDisabledControlText() const
{
    return this->disabledControlText;
}

terminal::colorPairId_t terminal::controlStyles::ControlStyleColorPallette::GetControlBorder() const
{
    return this->controlBorder;
}

terminal::colorPairId_t terminal::controlStyles::ControlStyleColorPallette::GetInactiveControlBorder() const
{
    return this->inactiveControlBorder;
}

terminal::colorPairId_t terminal::controlStyles::ControlStyleColorPallette::GetDisabledControlBorder() const
{
    return this->disabledControlBorder;
}

void terminal::controlStyles::ControlStyleColorPallette::SetControlText(terminal::colorPairId_t value)
{
    this->controlText = value;
}

void terminal::controlStyles::ControlStyleColorPallette::SetDisabledControlText(terminal::colorPairId_t value)
{
    this->disabledControlText = value;
}

void terminal::controlStyles::ControlStyleColorPallette::SetControlBorder(terminal::colorPairId_t value)
{
    this->controlBorder = value;
}

void terminal::controlStyles::ControlStyleColorPallette::SetInactiveControlBorder(terminal::colorPairId_t value)
{
    this->inactiveControlBorder = value;
}

void terminal::controlStyles::ControlStyleColorPallette::SetDisabledControlBorder(terminal::colorPairId_t value)
{
    this->disabledControlBorder = value;
}

json::Node *terminal::controlStyles::ControlStyleColorPallette::Serialize()
{
    auto node = this->terminal::ColorPallette::Serialize();

    if (node != nullptr)
    {
        auto obj = dynamic_cast<json::ObjectNode *>(node);

        if (obj != nullptr)
        {
            obj->Put("controlText", new json::PrimitiveNode(this->controlText));
            obj->Put("disabledControlText", new json::PrimitiveNode(this->disabledControlText));
            obj->Put("controlBorder", new json::PrimitiveNode(this->controlBorder));
            obj->Put("inactiveControlBorder", new json::PrimitiveNode(this->inactiveControlBorder));
            obj->Put("disabledControlBorder", new json::PrimitiveNode(this->disabledControlBorder));
        }
    }

    return node;
}

void terminal::controlStyles::ControlStyleColorPallette::Deserialize(const json::Node *)
{
}
