#include "terminal/canvas.hpp"

terminal::pattern::pattern() : items(),
                               total_length(0)
{
}

terminal::pattern::pattern(const pattern &copy) : items(copy.items),
                                                  total_length(copy.total_length)
{
}

terminal::pattern &terminal::pattern::push(const pattern_item &newItem)
{
    this->items.push_back(newItem);

    return *this;
    this->total_length += newItem.length;
}

terminal::pattern &terminal::pattern::push(char c)
{
    pattern_item newItem;
    newItem.symbol = c;
    newItem.length = 1;
    newItem.use_custom_attributes = false;
    newItem.use_custom_color = false;

    this->total_length += 1;
    this->items.push_back(newItem);

    return *this;
}

terminal::pattern &terminal::pattern::push(char c, int count)
{
    pattern_item newItem;
    newItem.symbol = c;
    newItem.length = count;
    newItem.use_custom_attributes = false;
    newItem.use_custom_color = false;

    this->total_length += count;
    this->items.push_back(newItem);

    return *this;
}

terminal::pattern &terminal::pattern::push(char c, const util::color &color)
{
    pattern_item newItem;
    newItem.symbol = c;
    newItem.length = 1;
    newItem.use_custom_attributes = false;
    newItem.use_custom_color = true;
    newItem.custom_color = color;

    this->total_length += 1;
    this->items.push_back(newItem);

    return *this;
}

terminal::pattern &terminal::pattern::push(char c, int count, const util::color &color)
{
    pattern_item newItem;
    newItem.symbol = c;
    newItem.length = count;
    newItem.use_custom_attributes = false;
    newItem.use_custom_color = true;
    newItem.custom_color = color;

    this->total_length += count;
    this->items.push_back(newItem);

    return *this;
}

terminal::pattern &terminal::pattern::push(char c, terminal::output_attribute a)
{
    pattern_item newItem;
    newItem.symbol = c;
    newItem.length = 1;
    newItem.use_custom_attributes = true;
    newItem.custom_attributes = a;
    newItem.use_custom_color = false;

    this->total_length += 1;
    this->items.push_back(newItem);

    return *this;
}

terminal::pattern &terminal::pattern::push(char c, int count, terminal::output_attribute a)
{
    pattern_item newItem;
    newItem.symbol = c;
    newItem.length = count;
    newItem.use_custom_attributes = true;
    newItem.custom_attributes = a;
    newItem.use_custom_color = false;

    this->total_length += count;
    this->items.push_back(newItem);

    return *this;
}

terminal::pattern &terminal::pattern::push(char c, const util::color &color, terminal::output_attribute a)
{
    pattern_item newItem;
    newItem.symbol = c;
    newItem.length = 1;
    newItem.use_custom_attributes = true;
    newItem.custom_attributes = a;
    newItem.use_custom_color = true;
    newItem.custom_color = color;

    this->total_length += 1;
    this->items.push_back(newItem);

    return *this;
}

terminal::pattern &terminal::pattern::push(char c, int count, const util::color &color, terminal::output_attribute a)
{
    pattern_item newItem;
    newItem.symbol = c;
    newItem.length = count;
    newItem.use_custom_attributes = true;
    newItem.custom_attributes = a;
    newItem.use_custom_color = true;
    newItem.custom_color = color;

    this->total_length += count;
    this->items.push_back(newItem);

    return *this;
}

void terminal::pattern::pop()
{
    if (!this->items.empty())
    {
        this->total_length -= this->items.back().length;
        this->items.pop_back();
    }
}

uint terminal::pattern::get_total_length()
{
    return this->total_length;
}

uint terminal::pattern::get_item_count()
{
    return this->items.size();
}
