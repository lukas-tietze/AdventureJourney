#include "json.hpp"

json::array_node::array_node() : node(),
                                 children()
{
}

json::array_node::~array_node()
{
    for (auto &node : this->children)
    {
        delete node;
    }
}

json::value_type json::array_node::get_type() const
{
    return json::value_type::Array;
}

void json::array_node::put(const std::string &value)
{
    this->put(new json::primitive_node(value));
}

void json::array_node::put(double value)
{
    this->put(new json::primitive_node(value));
}

void json::array_node::put(bool value)
{
    this->put(new json::primitive_node(value));
}

void json::array_node::put(json::node *value)
{
    this->children.push_back(value);
}

void json::array_node::put_null()
{
    this->put(new json::primitive_node());
}

void json::array_node::insert(int at, const std::string &value)
{
    this->insert(at, new json::primitive_node(value));
}

void json::array_node::insert(int at, double value)
{
    this->insert(at, new json::primitive_node(value));
}

void json::array_node::insert(int at, bool value)
{
    this->insert(at, new json::primitive_node(value));
}

void json::array_node::insert(int at, json::node *value)
{
    if (at < 0 || at > this->children.size())
        throw util::index_out_of_range_exception(at, this->children.size());

    if (at == this->children.size())
        this->children.push_back(value);
    else
        this->children.insert(this->children.begin() + at, value);
}

void json::array_node::insert_null(int at)
{
    this->insert(at, new json::primitive_node());
}

int json::array_node::get_child_count()
{
    return this->children.size();
}

json::node *json::array_node::get(int index)
{
    if (index < 0 || index >= this->children.size())
        throw util::index_out_of_range_exception(index, this->children.size());

    return this->children.at(index);
}

const json::node *json::array_node::get(int index) const
{
    if (index < 0 || index >= this->children.size())
        throw util::index_out_of_range_exception(index, this->children.size());

    return this->children.at(index);
}

bool json::array_node::try_get(int index, json::node *&buf) const
{
    if (index < 0 || index >= this->children.size())
        return false;

    buf = this->children.at(index);

    return true;
}

std::ostream &json::array_node::operator<<(std::ostream &stream) const
{
    stream << '[';

    auto it = this->children.begin();
    auto end = this->children.end();

    if (it != end)
    {
        stream << "\n";
        (*it)->operator<<(stream);
    }

    while (++it != end)
    {
        stream << ",\n";
        (*it)->operator<<(stream);
    }

    stream << "\n]";

    return stream;
}

json::formatted_printer &json::array_node::print_formatted(json::formatted_printer &p) const
{
    auto it = this->children.begin();
    auto end = this->children.end();

    p.begin_array();

    while (it != end)
    {
        (*it)->print_formatted(p);
        it++;
    }

    p.end_array();

    return p;
}