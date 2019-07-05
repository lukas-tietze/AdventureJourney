#include "Calculator.hpp"

util::LazyValue::LazyValue(const std::string &) : IValue(ValueType::String)
{
}

const std::string &util::LazyValue::GetValueAsString() const
{
    throw NotImplementedException();
}

double util::LazyValue::GetValueAsNumber() const
{
    throw NotImplementedException();
}

const util::ValueSet &util::LazyValue::GetValueAsSet() const
{
    throw NotImplementedException();
}

void util::LazyValue::PrintValueDescription(std::ostream &s) const
{
}
