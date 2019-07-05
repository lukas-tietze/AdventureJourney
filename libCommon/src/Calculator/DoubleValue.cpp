#include "Calculator.hpp"

util::DoubleValue::DoubleValue() : IValue(ValueType::Number),
                                   value()
{
}

util::DoubleValue::DoubleValue(double value) : IValue(ValueType::Number),
                                               value(value)
{
}

const std::string &util::DoubleValue::GetValueAsString() const
{
    throw NotSupportedException();
}

double util::DoubleValue::GetValueAsNumber() const
{
    return this->value;
}

const util::ValueSet &util::DoubleValue::GetValueAsSet() const
{
    throw NotSupportedException();
}

void util::DoubleValue::PrintValueDescription(std::ostream &s) const
{
}
