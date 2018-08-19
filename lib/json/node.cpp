#include "json.hpp"

json::node::~node()
{
}

std::ostream &json::node::operator<<(std::ostream &stream) const
{
    return stream;
}

void json::node::map(json::i_json_mappable *item)
{
    auto objectNode = static_cast<json::object_node *>(this);

    if (this->get_type() != json::value_type::Object || objectNode == nullptr)
        throw util::exception("Can only map object-nodes to objects");

    auto start = objectNode->begin();
    auto end = objectNode->end();
}