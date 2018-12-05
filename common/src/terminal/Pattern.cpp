#include "terminal/Canvas.hpp"

terminal::Pattern::Pattern() : items(),
                               totalLength(0)
{
}

terminal::Pattern::Pattern(const Pattern &copy) : items(copy.items),
                                                  totalLength(copy.totalLength)
{
}

terminal::Pattern &terminal::Pattern::Push(const PatternItem &newItem)
{
    this->items.push_back(newItem);

    return *this;
    this->totalLength += newItem.length;
}

terminal::Pattern &terminal::Pattern::Push(char c)
{
    PatternItem newItem;
    newItem.symbol = c;
    newItem.length = 1;
    newItem.useCustomAttributes = false;
    newItem.useCustomColor = false;

    this->totalLength += 1;
    this->items.push_back(newItem);

    return *this;
}

terminal::Pattern &terminal::Pattern::Push(char c, int count)
{
    PatternItem newItem;
    newItem.symbol = c;
    newItem.length = count;
    newItem.useCustomAttributes = false;
    newItem.useCustomColor = false;

    this->totalLength += count;
    this->items.push_back(newItem);

    return *this;
}

terminal::Pattern &terminal::Pattern::Push(char c, const util::Color &color)
{
    PatternItem newItem;
    newItem.symbol = c;
    newItem.length = 1;
    newItem.useCustomAttributes = false;
    newItem.useCustomColor = true;
    newItem.customColor = color;

    this->totalLength += 1;
    this->items.push_back(newItem);

    return *this;
}

terminal::Pattern &terminal::Pattern::Push(char c, int count, const util::Color &color)
{
    PatternItem newItem;
    newItem.symbol = c;
    newItem.length = count;
    newItem.useCustomAttributes = false;
    newItem.useCustomColor = true;
    newItem.customColor = color;

    this->totalLength += count;
    this->items.push_back(newItem);

    return *this;
}

terminal::Pattern &terminal::Pattern::Push(char c, terminal::OutputAttribute a)
{
    PatternItem newItem;
    newItem.symbol = c;
    newItem.length = 1;
    newItem.useCustomAttributes = true;
    newItem.customAttributes = a;
    newItem.useCustomColor = false;

    this->totalLength += 1;
    this->items.push_back(newItem);

    return *this;
}

terminal::Pattern &terminal::Pattern::Push(char c, int count, terminal::OutputAttribute a)
{
    PatternItem newItem;
    newItem.symbol = c;
    newItem.length = count;
    newItem.useCustomAttributes = true;
    newItem.customAttributes = a;
    newItem.useCustomColor = false;

    this->totalLength += count;
    this->items.push_back(newItem);

    return *this;
}

terminal::Pattern &terminal::Pattern::Push(char c, const util::Color &color, terminal::OutputAttribute a)
{
    PatternItem newItem;
    newItem.symbol = c;
    newItem.length = 1;
    newItem.useCustomAttributes = true;
    newItem.customAttributes = a;
    newItem.useCustomColor = true;
    newItem.customColor = color;

    this->totalLength += 1;
    this->items.push_back(newItem);

    return *this;
}

terminal::Pattern &terminal::Pattern::Push(char c, int count, const util::Color &color, terminal::OutputAttribute a)
{
    PatternItem newItem;
    newItem.symbol = c;
    newItem.length = count;
    newItem.useCustomAttributes = true;
    newItem.customAttributes = a;
    newItem.useCustomColor = true;
    newItem.customColor = color;

    this->totalLength += count;
    this->items.push_back(newItem);

    return *this;
}

void terminal::Pattern::Pop()
{
    if (!this->items.empty())
    {
        this->totalLength -= this->items.back().length;
        this->items.pop_back();
    }
}

uint terminal::Pattern::GetTotalLength()
{
    return this->totalLength;
}

uint terminal::Pattern::GetItemCount()
{
    return this->items.size();
}
