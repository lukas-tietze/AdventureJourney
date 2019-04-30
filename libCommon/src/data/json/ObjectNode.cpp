#include "data/Json.hpp"

json::ObjectNode::ObjectNode() : Node(),
                                 children()
{
}

json::ObjectNode::~ObjectNode()
{
    for (const auto &kvp : this->children)
    {
        delete kvp.second;
    }
}

json::ValueType json::ObjectNode::GetType() const
{
    return json::ValueType::Object;
}

void json::ObjectNode::Put(const std::string &name, const std::string &value)
{
    this->Put(name, new json::PrimitiveNode(value));
}

void json::ObjectNode::Put(const std::string &name, const char *value)
{
    this->Put(name, new json::PrimitiveNode(value));
}

void json::ObjectNode::Put(const std::string &name, double value)
{
    this->Put(name, new json::PrimitiveNode(value));
}

void json::ObjectNode::Put(const std::string &name, int value)
{
    this->Put(name, new json::PrimitiveNode(value));
}

void json::ObjectNode::Put(const std::string &name, bool value)
{
    this->Put(name, new json::PrimitiveNode(value));
}

void json::ObjectNode::Put(const std::string &name, json::Node *value)
{
    this->quickAccess.insert(std::make_pair(name, this->children.size()));
    this->children.push_back(std::make_pair(name, value));
}

void json::ObjectNode::PutNull(const std::string &name)
{
    this->Put(name, new json::PrimitiveNode());
}

bool json::ObjectNode::HasChild(const std::string &name) const
{
    return this->quickAccess.find(name) != this->quickAccess.end();
}

int json::ObjectNode::GetChildCount() const
{
    return this->children.size();
}

json::Node *json::ObjectNode::Get(const std::string &name)
{
    auto it = this->quickAccess.find(name);

    if (it == this->quickAccess.end())
        throw util::MissingKeyException();

    return this->children[it->second].second;
}

const json::Node *json::ObjectNode::Get(const std::string &name) const
{
    auto it = this->quickAccess.find(name);

    if (it == this->quickAccess.end())
        throw util::MissingKeyException();

    return this->children[it->second].second;
}

bool json::ObjectNode::TryGet(const std::string &name, json::Node *&buf) const
{
    auto it = this->quickAccess.find(name);

    if (it == this->quickAccess.end())
        return false;

    buf = this->children[it->second].second;

    return true;
}

std::ostream &json::ObjectNode::operator<<(std::ostream &stream) const
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

json::FormattedPrinter &json::ObjectNode::PrintFormatted(json::FormattedPrinter &p) const
{
    auto it = this->children.begin();
    auto end = this->children.end();

    p.BeginObject();

    while (it != end)
    {
        p.PrintProperty(it->first);
        it->second->PrintFormatted(p);
        it++;
    }

    p.EndObject();

    return p;
}

json::ObjectNode::ChildIterator json::ObjectNode::begin()
{
    return this->children.begin();
}

json::ObjectNode::ConstChildIterator json::ObjectNode::begin() const
{
    return this->children.begin();
}

json::ObjectNode::ChildIterator json::ObjectNode::end()
{
    return this->children.end();
}

json::ObjectNode::ConstChildIterator json::ObjectNode::end() const
{
    return this->children.end();
}

bool json::ObjectNode::operator==(const json::Node &other) const
{
    if (auto objectNode = dynamic_cast<const json::ObjectNode *>(&other))
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

bool json::ObjectNode::operator!=(const json::Node &other) const
{
    return !((*this) == other);
}
