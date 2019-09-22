#include "libCommon/Calculator.hpp"

calculator::LazyValue::LazyValue(const std::string &) : IValue(ValueType::String)
{
}

const std::string &calculator::LazyValue::GetValueAsString() const
{
    throw util::NotImplementedException();
}

double calculator::LazyValue::GetValueAsNumber() const
{
    throw util::NotImplementedException();
}

const calculator::ValueSet &calculator::LazyValue::GetValueAsSet() const
{
    throw util::NotImplementedException();
}

void calculator::LazyValue::PrintValueDescription(std::ostream &s) const
{
}
