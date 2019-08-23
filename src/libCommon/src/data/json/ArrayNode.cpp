#include "data/Json.hpp"

json::ArrayNode::ArrayNode() : Node(),
                               children()
{
}

json::ArrayNode::~ArrayNode()
{
    for (auto &Node : this->children)
    {
        delete Node;
    }
}

json::ValueType json::ArrayNode::GetType() const
{
    return json::ValueType::Array;
}

void json::ArrayNode::Put(const std::string &value)
{
    this->Put(new json::PrimitiveNode(value));
}

void json::ArrayNode::Put(const char *value)
{
    this->Put(new json::PrimitiveNode(value));
}

void json::ArrayNode::Put(double value)
{
    this->Put(new json::PrimitiveNode(value));
}

void json::ArrayNode::Put(int value)
{
    this->Put(new json::PrimitiveNode(value));
}

void json::ArrayNode::Put(bool value)
{
    this->Put(new json::PrimitiveNode(value));
}

void json::ArrayNode::Put(json::Node *value)
{
    this->children.push_back(value);
}

void json::ArrayNode::PutNull()
{
    this->Put(new json::PrimitiveNode());
}

void json::ArrayNode::Insert(uint at, const std::string &value)
{
    this->Insert(at, new json::PrimitiveNode(value));
}

void json::ArrayNode::Insert(uint at, const char *value)
{
    this->Insert(at, new json::PrimitiveNode(value));
}

void json::ArrayNode::Insert(uint at, double value)
{
    this->Insert(at, new json::PrimitiveNode(value));
}

void json::ArrayNode::Insert(uint at, int value)
{
    this->Insert(at, new json::PrimitiveNode(value));
}

void json::ArrayNode::Insert(uint at, bool value)
{
    this->Insert(at, new json::PrimitiveNode(value));
}

void json::ArrayNode::Insert(uint at, json::Node *value)
{
    if (at > this->children.size())
        throw util::IndexOutOfRangeException(at, this->children.size());

    if (at == this->children.size())
        this->children.push_back(value);
    else
        this->children.insert(this->children.begin() + at, value);
}

void json::ArrayNode::InsertNull(uint at)
{
    this->Insert(at, new json::PrimitiveNode());
}

int json::ArrayNode::GetChildCount() const
{
    return this->children.size();
}

json::Node *json::ArrayNode::Get(uint index)
{
    if (index >= this->children.size())
        throw util::IndexOutOfRangeException(index, this->children.size());

    return this->children.at(index);
}

const json::Node *json::ArrayNode::Get(uint index) const
{
    if (index >= this->children.size())
        throw util::IndexOutOfRangeException(index, this->children.size());

    return this->children.at(index);
}

bool json::ArrayNode::TryGet(uint index, json::Node *&buf) const
{
    if (index >= this->children.size())
        return false;

    buf = this->children.at(index);

    return true;
}

std::ostream &json::ArrayNode::operator<<(std::ostream &stream) const
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

json::FormattedPrinter &json::ArrayNode::PrintFormatted(json::FormattedPrinter &p) const
{
    auto it = this->children.begin();
    auto end = this->children.end();

    p.BeginArray();

    while (it != end)
    {
        (*it)->PrintFormatted(p);
        it++;
    }

    p.EndArray();

    return p;
}

json::ArrayNode::ChildIterator json::ArrayNode::begin()
{
    return this->children.begin();
}

json::ArrayNode::ConstChildIterator json::ArrayNode::begin() const
{
    return this->children.begin();
}

json::ArrayNode::ChildIterator json::ArrayNode::end()
{
    return this->children.end();
}

json::ArrayNode::ConstChildIterator json::ArrayNode::end() const
{
    return this->children.end();
}

bool json::ArrayNode::operator==(const json::Node &other) const
{
    if (auto arrayNode = dynamic_cast<const json::ArrayNode *>(&other))
    {
        if (this->children.size() == arrayNode->children.size())
        {
            for (uint i = 0, end = this->children.size(); i < end; i++)
            {
                if (this->children[i] != arrayNode->children[i])
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

bool json::ArrayNode::operator!=(const json::Node &other) const
{
    return !((*this) == other);
}
