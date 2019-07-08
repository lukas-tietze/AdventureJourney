#include "Calculator.hpp"

calculator::DoubleValue::DoubleValue() : IValue(ValueType::Number),
                                         value()
{
}

calculator::DoubleValue::DoubleValue(double value) : IValue(ValueType::Number),
                                                     value(value)
{
}

const std::string &calculator::DoubleValue::GetValueAsString() const
{
    throw util::NotSupportedException();
}

double calculator::DoubleValue::GetValueAsNumber() const
{
    return this->value;
}

const calculator::ValueSet &calculator::DoubleValue::GetValueAsSet() const
{
    throw util::NotSupportedException();
}

void calculator::DoubleValue::PrintValueDescription(std::ostream &s) const
{
}
