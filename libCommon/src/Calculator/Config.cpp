#include "Calculator.hpp"

util::Config::Config()
{
}

void util::Config::CreateDefaultConfig()
{
}

void util::Config::AddOperator(const std::string &, Operator *)
{
}

void util::Config::AddFunction(const std::string &, function_t)
{
}

void util::Config::AddVariable(const std::string &, IValue *)
{
}

bool util::Config::RemoveOperator(char)
{
}

bool util::Config::RemoveFunction(const std::string &)
{
}

bool util::Config::RemoveVariable(const std::string &)
{
}

void util::Config::SetBrackets(char, char)
{
}

void util::Config::SetBracketMarker(char, char)
{
}

void util::Config::SetStringMarker(char, char)
{
}

void util::Config::SetLazyEvalMarker(char, char)
{
}

void util::Config::SetFunctionBrackets(char, char)
{
}

void util::Config::SetSetMarkers(char, char)
{
}

void util::Config::SetAccessorMarkers(char, char)
{
}

void util::Config::GetListSeperator(char)
{
}

void util::Config::SetDecimalSeperator(char)
{
}

void util::Config::SetFunctionParameterSeperator(char)
{
}

void util::Config::SetStringEscapeMarker(char)
{
}

std::unordered_map<std::string, util::function_t> &util::Config::GetFunctions()
{
}

std::unordered_map<std::string, util::Operator *> &util::Config::GetOperators()
{
}

std::unordered_map<std::string, util::IValue *> &util::Config::GetVariables()
{
}

util::Operator *util::Config::GetOperator(const std::string &)
{
}

util::function_t util::Config::GetFunction(const std::string &)
{
}

util::IValue *util::Config::GetVariable(const std::string &)
{
}

util::Config::CharPair &util::Config::GetBrackets()
{
}

util::Config::CharPair &util::Config::GetBracketMarker()
{
}

util::Config::CharPair &util::Config::GetStringMarker()
{
}

util::Config::CharPair &util::Config::GetLazyEvalMarker()
{
}

util::Config::CharPair &util::Config::GetFunctionBrackets()
{
}

util::Config::CharPair &util::Config::GetSetMarkers()
{
}

util::Config::CharPair &util::Config::GetAccessorMarkers()
{
}

const std::unordered_map<std::string, util::function_t> &util::Config::GetFunctions() const
{
}

const std::unordered_map<std::string, util::Operator *> &util::Config::GetOperators() const
{
}

const std::unordered_map<std::string, util::IValue *> &util::Config::GetVariables() const
{
}

const util::Operator *util::Config::GetOperator(const std::string &) const
{
}

const util::function_t util::Config::GetFunction(const std::string &) const
{
}

const util::IValue *util::Config::GetVariable(const std::string &) const
{
}

const util::Config::CharPair &util::Config::GetBrackets() const
{
}

const util::Config::CharPair &util::Config::GetBracketMarker() const
{
}

const util::Config::CharPair &util::Config::GetStringMarker() const
{
}

const util::Config::CharPair &util::Config::GetLazyEvalMarker() const
{
}

const util::Config::CharPair &util::Config::GetFunctionBrackets() const
{
}

const util::Config::CharPair &util::Config::GetSetMarkers() const
{
}

const util::Config::CharPair &util::Config::GetAccessorMarkers() const
{
}

char util::Config::GetListSeperator() const
{
}

char util::Config::GetDecimalSeperator() const
{
}

char util::Config::GetFunctionParameterSeperator() const
{
}

char util::Config::GetStringEscapeMarker() const
{
}
