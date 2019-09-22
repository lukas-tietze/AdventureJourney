#include "libCommon/Calculator.hpp"

calculator::StringValue::StringValue() : IValue(ValueType::String),
                                   value()
{
}

calculator::StringValue::StringValue(const std::string &value) : IValue(ValueType::String),
                                                           value(value)
{
}

const std::string &calculator::StringValue::GetValueAsString() const
{
    return this->value;
}

double calculator::StringValue::GetValueAsNumber() const
{
    throw util::NotSupportedException();
}

const calculator::ValueSet &calculator::StringValue::GetValueAsSet() const
{
    throw util::NotSupportedException();
}

void calculator::StringValue::PrintValueDescription(std::ostream &s) const
{
}
