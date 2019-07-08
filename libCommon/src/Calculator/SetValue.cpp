#include "Calculator.hpp"

calculator::SetValue::SetValue() : IValue(ValueType::Set),
                                   value()
{
}

calculator::SetValue::SetValue(const std::initializer_list<IValue *> values) : IValue(ValueType::Set),
                                                                               value(values)
{
}

const std::string &calculator::SetValue::GetValueAsString() const
{
    throw util::NotSupportedException();
}

double calculator::SetValue::GetValueAsNumber() const
{
    throw util::NotSupportedException();
}

const calculator::ValueSet &calculator::SetValue::GetValueAsSet() const
{
    return this->value;
}

void calculator::SetValue::PrintValueDescription(std::ostream &s) const
{
}
