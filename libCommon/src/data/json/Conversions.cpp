#include "data/Json.hpp"

std::ostream &json::operator<<(std::ostream &stream, const json::Token &token)
{
    stream << "[" << token.type << "] \"" << std::string(token.data, token.dataLen) << "\"";

    return stream;
}

std::ostream &json::operator<<(std::ostream &stream, const json::TokenType &tokenType)
{
    switch (tokenType)
    {
    case json::TokenType::String:
        stream << "String";
        break;
    case json::TokenType::Number:
        stream << "Number";
        break;
    case json::TokenType::ArrayStart:
        stream << "ArrayStart";
        break;
    case json::TokenType::ArrayEnd:
        stream << "ArrayEnd";
        break;
    case json::TokenType::ObjectStart:
        stream << "ObjectStart";
        break;
    case json::TokenType::ObjectEnd:
        stream << "ObjectEnd";
        break;
    case json::TokenType::ValueAssignment:
        stream << "ObjectAssignment";
        break;
    case json::TokenType::ValueSeperator:
        stream << "ObjectSeperator";
        break;
    case json::TokenType::ValueTrue:
        stream << "ValueTrue";
        break;
    case json::TokenType::ValueFalse:
        stream << "ValueFalse";
        break;
    case json::TokenType::ValueNull:
        stream << "ValueNull";
        break;
    default:
        throw std::exception();
    }

    return stream;
}

std::ostream &json::operator<<(std::ostream &stream, const ValueType &value)
{
    switch (value)
    {
    case json::ValueType::String:
        stream << "String";
        break;
    case json::ValueType::Number:
        stream << "Number";
        break;
    case json::ValueType::Object:
        stream << "Object";
        break;
    case json::ValueType::Array:
        stream << "Array";
        break;
    case json::ValueType::True:
        stream << "True";
        break;
    case json::ValueType::False:
        stream << "False";
        break;
    case json::ValueType::Null:
        stream << "Null";
        break;
    default:
        throw std::exception();
    }

    return stream;
}