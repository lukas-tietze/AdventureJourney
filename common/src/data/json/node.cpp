#include "data/json.hpp"

json::node::~node()
{
}

std::ostream &json::node::operator<<(std::ostream &stream) const
{
    return stream;
}