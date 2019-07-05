#include "Calculator.hpp"

util::SetValue::SetValue() : IValue(ValueType::Set),
                             value()
{
}

util::SetValue::SetValue(const std::initializer_list<IValue *> values) : IValue(ValueType::Set),
                                                                         value(values)
{
}

const std::string &util::SetValue::GetValueAsString() const
{
    throw NotSupportedException();
}

double util::SetValue::GetValueAsNumber() const
{
    throw NotSupportedException();
}

const util::ValueSet &util::SetValue::GetValueAsSet() const
{
    return this->value;
}

void util::SetValue::PrintValueDescription(std::ostream &s) const
{
}
