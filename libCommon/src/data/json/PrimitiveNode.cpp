#include "data/Json.hpp"
#include "Exception.hpp"
#include "data/String.hpp"

json::PrimitiveNode::PrimitiveNode(const std::string &value) : Node(),
                                                               stringValue(value),
                                                               numericValue(0),
                                                               type(json::ValueType::String)
{
}

json::PrimitiveNode::PrimitiveNode(const char *value) : Node(),
                                                        stringValue(value),
                                                        numericValue(0),
                                                        type(json::ValueType::String)
{
}

json::PrimitiveNode::PrimitiveNode(double value) : Node(),
                                                   stringValue(""),
                                                   numericValue(value),
                                                   type(json::ValueType::Number)
{
}

json::PrimitiveNode::PrimitiveNode(int value) : Node(),
                                                stringValue(""),
                                                numericValue(value),
                                                type(json::ValueType::Number)
{
}

json::PrimitiveNode::PrimitiveNode(bool value) : Node(),
                                                 stringValue(""),
                                                 numericValue(0),
                                                 type(value ? json::ValueType::True : json::ValueType::False)
{
}

json::PrimitiveNode::PrimitiveNode() : Node(),
                                       stringValue(""),
                                       numericValue(0),
                                       type(json::ValueType::Null)
{
}

json::PrimitiveNode::~PrimitiveNode()
{
}

json::ValueType json::PrimitiveNode::GetType() const
{
    return this->type;
}

const std::string &json::PrimitiveNode::GetValueAsString() const
{
    if (this->type != json::ValueType::String)
    {
        throw json::ValueException();
    }

    return this->stringValue;
}

double json::PrimitiveNode::GetValueAsNumber() const
{
    if (this->type != json::ValueType::Number)
    {
        throw json::ValueException();
    }

    return this->numericValue;
}

bool json::PrimitiveNode::IsValueNull() const
{
    return this->type == json::ValueType::Null;
}

bool json::PrimitiveNode::GetValueAsBool() const
{
    if (this->type == json::ValueType::True)
        return true;
    else if (this->type == json::ValueType::False)
        return false;
    else
        throw json::ValueException();
}

bool json::PrimitiveNode::TryGetValueAsString(std::string &s) const
{
    if (this->GetType() == json::ValueType::String)
    {
        s.assign(this->stringValue);
        return true;
    }
    else
    {
        return false;
    }
}

bool json::PrimitiveNode::TryGetValueAsNumber(double &d) const
{
    if (this->GetType() == json::ValueType::Number)
    {
        d = this->numericValue;
        return true;
    }
    else
    {
        return false;
    }
}

bool json::PrimitiveNode::TryGetValueAsBool(bool &b) const
{
    if (this->GetType() == json::ValueType::True)
    {
        b = true;
        return true;
    }
    else if (this->GetType() == json::ValueType::False)
    {
        b = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool json::PrimitiveNode::TryGetValueAsStringOrDefault(std::string &target, const std::string &defaultValue) const
{
    auto res = this->TryGetValueAsString(target);

    if (!res)
        target = defaultValue;

    return res;
}

bool json::PrimitiveNode::TryGetValueAsNumberOrDefault(double &target, double defaultValue) const
{
    auto res = this->TryGetValueAsNumber(target);

    if (!res)
        target = defaultValue;

    return res;
}

bool json::PrimitiveNode::TryGetValueAsBoolOrDefault(bool &target, bool defaultValue) const
{
    auto res = this->TryGetValueAsBool(target);

    if (!res)
        target = defaultValue;

    return res;
}

void json::PrimitiveNode::SetValue(bool value)
{
    this->ClearValues();
    this->type = value ? json::ValueType::True : json::ValueType::False;
}

void json::PrimitiveNode::SetValueNull()
{
    this->ClearValues();
    this->type = json::ValueType::Null;
}

void json::PrimitiveNode::SetValue(const std::string &stringValue)
{
    this->ClearValues();
    this->type = json::ValueType::String;
    this->stringValue.assign(stringValue);
}

void json::PrimitiveNode::SetValue(double doubleValue)
{
    this->ClearValues();
    this->type = json::ValueType::Number;
    this->numericValue = doubleValue;
}

void json::PrimitiveNode::ClearValues()
{
    this->numericValue = 0;
    this->stringValue.clear();
}

std::ostream &json::PrimitiveNode::operator<<(std::ostream &stream) const
{
    switch (this->GetType())
    {
    case json::ValueType::String:
        stream << this->stringValue;
        break;
    case json::ValueType::Number:
        stream << this->numericValue;
        break;
    case json::ValueType::True:
        stream << json::ValueTrue;
        break;
    case json::ValueType::False:
        stream << json::ValueFalse;
        break;
    case json::ValueType::Null:
        stream << json::ValueNull;
        break;
    case json::ValueType::Object:
    case json::ValueType::Array:
    default:
        throw util::InvalidCaseException();
        break;
    }

    return stream;
}

json::FormattedPrinter &json::PrimitiveNode::PrintFormatted(json::FormattedPrinter &p) const
{
    switch (this->GetType())
    {
    case json::ValueType::String:
        p.Print(this->stringValue);
        break;
    case json::ValueType::Number:
        p.Print(this->numericValue);
        break;
    case json::ValueType::True:
        p.PrintTrue();
        break;
    case json::ValueType::False:
        p.PrintFalse();
        break;
    case json::ValueType::Null:
        p.PrintNull();
        break;
    case json::ValueType::Object:
    case json::ValueType::Array:
    default:
        throw util::InvalidCaseException();
        break;
    }

    return p;
}

bool json::PrimitiveNode::operator==(const json::Node &other) const
{
    if (auto primitiveNode = dynamic_cast<const json::PrimitiveNode *>(&other))
    {
        if (this->type == primitiveNode->type)
        {
            switch (this->type)
            {
            case json::ValueType::String:
                return this->stringValue == primitiveNode->stringValue;
            case json::ValueType::Number:
                return this->numericValue == primitiveNode->numericValue;
            case json::ValueType::True:
            case json::ValueType::False:
            case json::ValueType::Null:
                return true;
            case json::ValueType::Object:
            case json::ValueType::Array:
                throw util::InvalidCaseException(util::ToString(this->type), "Illegal state");
            default:
                throw util::InvalidCaseException(util::ToString(this->type), "Unknown case");
            }
        }

        return false;
    }

    return false;
}

bool json::PrimitiveNode::operator!=(const json::Node &other) const
{
    return !((*this) == other);
}