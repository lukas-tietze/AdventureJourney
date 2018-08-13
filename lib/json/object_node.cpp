#include "json.hpp"

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

void json::object_node::put(const std::string &name, const std::string &value)
{
    this->put(name, new json::primitive_node(value));
}

void json::object_node::put(const std::string &name, double value)
{
    this->put(name, new json::primitive_node(value));
}

void json::object_node::put(const std::string &name, bool value)
{
    this->put(name, new json::primitive_node(value));
}

void json::object_node::put(const std::string &name, json::node *value)
{
    this->children.insert({name, value});
}

void json::object_node::put_null(const std::string &name)
{
    this->put(name, new json::primitive_node());
}

bool json::object_node::has_child(const std::string &name) const
{
    return this->children.find(name) != this->children.end();
}

int json::object_node::get_child_count() const
{
    return this->children.size();
}

json::node *json::object_node::get(const std::string &name)
{
    auto it = this->children.find(name);

    if (it == this->children.end())
        throw util::missing_key_exception();

    return it->second;
}

const json::node *json::object_node::get(const std::string &name) const
{
    auto it = this->children.find(name);

    if (it == this->children.end())
        throw util::missing_key_exception();

    return it->second;
}

bool json::object_node::try_get(const std::string &name, json::node *&buf) const
{
    auto it = this->children.find(name);

    if (it == this->children.end())
        return false;

    buf = it->second;

    return true;
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