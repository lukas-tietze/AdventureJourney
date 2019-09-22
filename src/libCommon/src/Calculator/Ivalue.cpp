#include "libCommon/Calculator.hpp"

calculator::IValue::IValue(ValueType type) : type(type)
{
}

calculator::IValue::~IValue()
{
}

calculator::ValueType calculator::IValue::GetType() const
{
    return this->type;
}

std::ostream &calculator::operator<<(std::ostream &s, const IValue &v)
{
    v.PrintValueDescription(s);

    return s;
}