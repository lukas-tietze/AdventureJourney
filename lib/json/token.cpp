#include "json.hpp"

std::ostream &json::operator<<(std::ostream &stream, const json::token &token)
{
    stream << "[" << token.type << "] \"" << std::string(token.data, token.data_len) << "\"";

    return stream;
}

std::ostream &json::operator<<(std::ostream &stream, const json::token_type &tokenType)
{
    switch (tokenType)
    {
    case json::token_type::String:
        stream << "String";
        break;
    case json::token_type::Number:
        stream << "Number";
        break;
    case json::token_type::ArrayStart:
        stream << "ArrayStart";
        break;
    case json::token_type::ArrayEnd:
        stream << "ArrayEnd";
        break;
    case json::token_type::ObjectStart:
        stream << "ObjectStart";
        break;
    case json::token_type::ObjectEnd:
        stream << "ObjectEnd";
        break;
    case json::token_type::ObjectAssignment:
        stream << "ObjectAssignment";
        break;
    case json::token_type::ObjectSeperator:
        stream << "ObjectSeperator";
        break;
    case json::token_type::ValueTrue:
        stream << "ValueTrue";
        break;
    case json::token_type::ValueFalse:
        stream << "ValueFalse";
        break;
    case json::token_type::ValueNull:
        stream << "ValueNull";
        break;
    default:
        throw std::exception();
        break;
    }

    return stream;
}