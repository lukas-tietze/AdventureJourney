#include "Calculator.hpp"

util::IValue::IValue(ValueType type) : type(type)
{
}

util::IValue::~IValue()
{
}

util::ValueType util::IValue::GetType() const
{
    return this->type;
}

std::ostream &util::operator<<(std::ostream &s, const IValue &v)
{
    v.PrintValueDescription(s);

    return s;
}