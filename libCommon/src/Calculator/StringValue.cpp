#include "Calculator.hpp"

util::StringValue::StringValue() : IValue(ValueType::String),
                                   value()
{
}

util::StringValue::StringValue(const std::string &value) : IValue(ValueType::String),
                                                           value(value)
{
}

const std::string &util::StringValue::GetValueAsString() const
{
    return this->value;
}

double util::StringValue::GetValueAsNumber() const
{
    throw NotSupportedException();
}

const util::ValueSet &util::StringValue::GetValueAsSet() const
{
    throw NotSupportedException();
}

void util::StringValue::PrintValueDescription(std::ostream &s) const
{
}
