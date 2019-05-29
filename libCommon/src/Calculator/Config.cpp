#include "Calculator.hpp"

util::Config::Config()
{
}

void util::Config::CreateDefaultConfig()
{
}

void util::Config::AddOperator(const std::string &name, Operator *op)
{
    this->operators[name] = op;
}

void util::Config::AddFunction(const std::string &name, function_t f)
{
    this->functions[name] = f;
}

void util::Config::AddVariable(const std::string &name, IValue *v)
{
    this->variables[name] = v;
}

bool util::Config::RemoveOperator(const std::string &name)
{
    return this->operators.erase(name);
}

bool util::Config::RemoveFunction(const std::string &name)
{
    return this->functions.erase(name);
}

bool util::Config::RemoveVariable(const std::string &name)
{
    return this->variables.erase(name);
}

void util::Config::SetBracketMarker(char opening, char closing)
{
    this->bracketMarker.opening = opening;
    this->bracketMarker.closing = closing;
}

void util::Config::SetStringMarker(char opening, char closing)
{
    this->stringMarker.opening = opening;
    this->stringMarker.closing = closing;
}

void util::Config::SetLazyEvalMarker(char opening, char closing)
{
    this->lazyEvalMarker.opening = opening;
    this->lazyEvalMarker.closing = closing;
}

void util::Config::SetFunctionBrackets(char opening, char closing)
{
    this->functionBrackets.opening = opening;
    this->functionBrackets.closing = closing;
}

void util::Config::SetSetMarkers(char opening, char closing)
{
    this->setMarkers.opening = opening;
    this->setMarkers.closing = closing;
}

void util::Config::SetAccessorMarkers(char opening, char closing)
{
    this->accessorMarkers.opening = opening;
    this->accessorMarkers.closing = closing;
}

void util::Config::GetListSeperator(char value)
{
    this->listSeperator = value;
}

void util::Config::SetDecimalSeperator(char value)
{
    this->decimalSeperator = value;
}

void util::Config::SetFunctionParameterSeperator(char value)
{
    this->functionParameterSeperator = value;
}

void util::Config::SetStringEscapeMarker(char value)
{
    this->stringEscapeMarker = value;
}

std::unordered_map<std::string, util::function_t> &util::Config::GetFunctions()
{
    return this->functions;
}

std::unordered_map<std::string, util::Operator *> &util::Config::GetOperators()
{
    return this->operators;
}

std::unordered_map<std::string, util::IValue *> &util::Config::GetVariables()
{
    return this->variables;
}

util::Operator *util::Config::GetOperator(const std::string &name)
{
    auto res = this->operators.find(name);

    return res == this->operators.end() ? nullptr : res->second;
}

util::function_t util::Config::GetFunction(const std::string &name)
{
    auto res = this->functions.find(name);

    return res == this->functions.end() ? nullptr : res->second;
}

util::IValue *util::Config::GetVariable(const std::string &name)
{
    auto res = this->variables.find(name);

    return res == this->variables.end() ? nullptr : res->second;
}

util::Config::CharPair &util::Config::GetBracketMarker()
{
    return this->bracketMarker;
}

util::Config::CharPair &util::Config::GetStringMarker()
{
    return this->stringMarker;
}

util::Config::CharPair &util::Config::GetLazyEvalMarker()
{
    return this->lazyEvalMarker;
}

util::Config::CharPair &util::Config::GetFunctionBrackets()
{
    return this->functionBrackets;
}

util::Config::CharPair &util::Config::GetSetMarkers()
{
    return this->setMarkers;
}

util::Config::CharPair &util::Config::GetAccessorMarkers()
{
    return this->accessorMarkers;
}

const std::unordered_map<std::string, util::function_t> &util::Config::GetFunctions() const
{
    return this->functions;
}

const std::unordered_map<std::string, util::Operator *> &util::Config::GetOperators() const
{
    return this->operators;
}

const std::unordered_map<std::string, util::IValue *> &util::Config::GetVariables() const
{
    return this->variables;
}

const util::Operator *util::Config::GetOperator(const std::string &name) const
{
    auto res = this->operators.find(name);

    return res == this->operators.end() ? nullptr : res->second;
}

const util::function_t util::Config::GetFunction(const std::string &name) const
{
    auto res = this->functions.find(name);

    return res == this->functions.end() ? nullptr : res->second;
}

const util::IValue *util::Config::GetVariable(const std::string &name) const
{
    auto res = this->variables.find(name);

    return res == this->variables.end() ? nullptr : res->second;
}

const util::Config::CharPair &util::Config::GetBracketMarker() const
{
    return this->bracketMarker;
}

const util::Config::CharPair &util::Config::GetStringMarker() const
{
    return this->stringMarker;
}

const util::Config::CharPair &util::Config::GetLazyEvalMarker() const
{
    return this->lazyEvalMarker;
}

const util::Config::CharPair &util::Config::GetFunctionBrackets() const
{
    return this->functionBrackets;
}

const util::Config::CharPair &util::Config::GetSetMarkers() const
{
    return this->setMarkers;
}

const util::Config::CharPair &util::Config::GetAccessorMarkers() const
{
    return this->accessorMarkers;
}

char util::Config::GetListSeperator() const
{
    return this->listSeperator;
}

char util::Config::GetDecimalSeperator() const
{
    return this->decimalSeperator;
}

char util::Config::GetFunctionParameterSeperator() const
{
    return this->functionParameterSeperator;
}

char util::Config::GetStringEscapeMarker() const
{
    return this->stringEscapeMarker;
}
