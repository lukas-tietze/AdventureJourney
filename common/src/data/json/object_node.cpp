#include "data/json.hpp"

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

void json::object_node::put(const std::string &name, const char *value)
{
    this->put(name, new json::primitive_node(value));
}

void json::object_node::put(const std::string &name, double value)
{
    this->put(name, new json::primitive_node(value));
}

void json::object_node::put(const std::string &name, int value)
{
    this->put(name, new json::primitive_node(value));
}

void json::object_node::put(const std::string &name, bool value)
{
    this->put(name, new json::primitive_node(value));
}

void json::object_node::put(const std::string &name, json::node *value)
{
    this->quick_access.insert(std::make_pair(name, this->children.size()));
    this->children.push_back(std::make_pair(name, value));
}

void json::object_node::put_null(const std::string &name)
{
    this->put(name, new json::primitive_node());
}

bool json::object_node::has_child(const std::string &name) const
{
    return this->quick_access.find(name) != this->quick_access.end();
}

int json::object_node::get_child_count() const
{
    return this->children.size();
}

json::node *json::object_node::get(const std::string &name)
{
    auto it = this->quick_access.find(name);

    if (it == this->quick_access.end())
        throw util::missing_key_exception();

    return this->children[it->second].second;
}

const json::node *json::object_node::get(const std::string &name) const
{
    auto it = this->quick_access.find(name);

    if (it == this->quick_access.end())
        throw util::missing_key_exception();

    return this->children[it->second].second;
}

bool json::object_node::try_get(const std::string &name, json::node *&buf) const
{
    auto it = this->quick_access.find(name);

    if (it == this->quick_access.end())
        return false;

    buf = this->children[it->second].second;

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

json::object_node::child_iterator json::object_node::begin()
{
    return this->children.begin();
}

json::object_node::const_child_iterator json::object_node::begin() const
{
    return this->children.begin();
}

json::object_node::child_iterator json::object_node::end()
{
    return this->children.end();
}

json::object_node::const_child_iterator json::object_node::end() const
{
    return this->children.end();
}

bool json::object_node::operator==(const json::node &other) const
{
    if (auto objectNode = dynamic_cast<const json::object_node *>(&other))
    {
        if (this->children.size() == objectNode->children.size())
        {
            for (uint i = 0, end = this->children.size(); i < end; i++)
            {
                if (this->children[i].first != objectNode->children[i].first ||
                    this->children[i].second != objectNode->children[i].second)
                {
                    return false;
                }

                return true;
            }
        }

        return false;
    }

    return false;
}

bool json::object_node::operator!=(const json::node &other) const
{
    return !((*this) == other);
}
