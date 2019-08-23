#include "data/Json.hpp"

json::Node::~Node()
{
}

std::ostream &json::Node::operator<<(std::ostream &stream) const
{
    return stream;
}