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
    if(this->get_type() != json::value_type::Object)
        throw util::exception("Can only map object-nodes to objects");

    // auto property

    // for(const auto &property : static_cast<json::object_node *>(this)->)
    // {
    //     /* code */
    // }
    
}