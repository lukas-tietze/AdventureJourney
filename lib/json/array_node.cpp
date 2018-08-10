#include "json.hpp"

json::array_node::array_node(const std::string &name) : node(name),
                                                        children()
{
}

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

const std::string &json::array_node::get_value_as_string() const
{
    throw json::operation_exception();
}

double json::array_node::get_value_as_number() const
{
    throw json::operation_exception();
}

const json::node *json::array_node::get_value_as_object() const
{
    throw json::operation_exception();
}

const std::vector<json::node *> &json::array_node::get_value_as_array() const
{
    return this->children;
}

const json::node *json::array_node::find_child(const std::string &name)
{
    throw json::operation_exception();
}

void json::array_node::add_child(json::node *node)
{
    this->children.push_back(node);
}

std::ostream &json::array_node::operator<<(std::ostream &stream) const
{
    stream << '[';

    auto it = this->children.begin();
    auto end = this->children.end();

    if (it != end)
    {
        stream << "\n" << *it;
    }

    while(++it != end)
    {
        stream << ",\n" << *it;
    }

    stream << "\n]";

    return stream;
}