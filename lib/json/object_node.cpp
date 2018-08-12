#include "json.hpp"

json::object_node::object_node(const std::string &name) : node(name),
                                                          children()
{
}

json::object_node::object_node() : node(),
                                   children()
{
}

json::object_node::~object_node()
{
    for (const auto &kvp : this->children)
    {
        delete kvp.second;
    }
}

json::value_type json::object_node::get_type() const
{
    return json::value_type::Object;
}

const std::string &json::object_node::get_value_as_string() const
{
    throw json::operation_exception();
}

double json::object_node::get_value_as_number() const
{
    throw json::operation_exception();
}

const json::node *json::object_node::get_value_as_object() const
{
    throw json::operation_exception();
}

const std::vector<json::node *> &json::object_node::get_value_as_array() const
{
    throw json::operation_exception();
}

const json::node *json::object_node::find_child(const std::string &name)
{
    auto res = this->children.find(name);

    if (res != this->children.end())
    {
        return (*res).second;
    }

    return nullptr;
}

void json::object_node::add_child(json::node *node)
{
    this->children.insert({node->get_name(), node});
}

std::ostream &json::object_node::operator<<(std::ostream &stream) const
{
    stream << '{';

    auto it = this->children.begin();
    auto end = this->children.end();

    if (it != end)
    {
        stream << "\n"
               << it->first << ": ";
        (it->second)->operator<<(stream);
    }

    while (++it != end)
    {
        stream << ",\n"
               << it->first << ": ";
        (it->second)->operator<<(stream);
    }

    stream << "\n}";

    return stream;
}

json::formatted_printer &json::object_node::print_formatted(json::formatted_printer &p) const
{
    auto it = this->children.begin();
    auto end = this->children.end();

    p.begin_object();

    while (it != end)
    {
        p.print_property(it->first);
        it->second->print_formatted(p);
        it++;
    }

    p.end_object();

    return p;
}