#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <set>

#include "data/Io.hpp"

namespace util
{
enum class ValueType
{
    String,
    Number,
    Set,
};

class IValue;
class EvaluationContext;

typedef IValue *(*function_t)(IValue *const *, int, EvaluationContext &);

class Operator
{
private:
    int priority;
    bool isUnary;
    function_t function;

public:
    Operator(int priority, bool isUnary, function_t function);

    int GetPriority() const;
    bool IsUnary() const;
    bool IsBinary() const;
    function_t GetFunction();
    const function_t GetFunction() const;
};

class ValueSet
{
private:
    std::vector<IValue *> values;

public:
    ValueSet();
    ValueSet(const std::initializer_list<IValue *> &);
};

class IValue
{
private:
    ValueType type;

public:
    IValue(ValueType type);
    virtual ~IValue();

    ValueType GetType() const;

    virtual const std::string &GetValueAsString() const = 0;
    virtual double GetValueAsNumber() const = 0;
    virtual const ValueSet &GetValueAsSet() const = 0;
    virtual void PrintValueDescription(std::ostream &) const = 0;
};

std::ostream &operator<<(std::ostream &, const IValue &);

class DoubleValue : public IValue
{
private:
    double value;

public:
    DoubleValue();
    DoubleValue(double value);

    const std::string &GetValueAsString() const;
    double GetValueAsNumber() const;
    const ValueSet &GetValueAsSet() const;
    void PrintValueDescription(std::ostream &) const;
};

class StringValue : public IValue
{
private:
    std::string value;

public:
    StringValue();
    StringValue(const std::string &value);

    const std::string &GetValueAsString() const;
    double GetValueAsNumber() const;
    const ValueSet &GetValueAsSet() const;
    void PrintValueDescription(std::ostream &) const;
};

class SetValue : public IValue
{
private:
    ValueSet value;

public:
    SetValue();
    SetValue(const std::initializer_list<IValue *> values);

    const std::string &GetValueAsString() const;
    double GetValueAsNumber() const;
    const ValueSet &GetValueAsSet() const;
    void PrintValueDescription(std::ostream &) const;
};

class LazyValue : public IValue
{
private:
public:
    LazyValue(const std::string &);

    const std::string &GetValueAsString() const;
    double GetValueAsNumber() const;
    const ValueSet &GetValueAsSet() const;
    void PrintValueDescription(std::ostream &) const;
};

class Config
{
public:
    struct CharPair
    {
        char opening;
        char closing;
    };

    Config();

    void CreateDefaultConfig();

    void AddOperator(const std::string &, Operator *);
    void AddFunction(const std::string &, function_t);
    void AddVariable(const std::string &, IValue *);

    bool RemoveOperator(const std::string &);
    bool RemoveFunction(const std::string &);
    bool RemoveVariable(const std::string &);

    void ClearOperators();
    void ClearFunctions();
    void ClearVariables();

    void SetBracketMarker(char, char);
    void SetStringMarker(char, char);
    void SetLazyEvalMarker(char, char);
    void SetFunctionBrackets(char, char);
    void SetSetMarkers(char, char);
    void SetAccessorMarkers(char, char);
    void GetListSeperator(char);
    void SetDecimalSeperator(char);
    void SetFunctionParameterSeperator(char);
    void SetStringEscapeMarker(char);

    std::unordered_map<std::string, function_t> &GetFunctions();
    std::unordered_map<std::string, Operator *> &GetOperators();
    std::unordered_map<std::string, IValue *> &GetVariables();
    Operator *GetOperator(const std::string &);
    function_t GetFunction(const std::string &);
    IValue *GetVariable(const std::string &);
    CharPair &GetBracketMarker();
    CharPair &GetStringMarker();
    CharPair &GetLazyEvalMarker();
    CharPair &GetFunctionBrackets();
    CharPair &GetSetMarkers();
    CharPair &GetAccessorMarkers();

    const std::unordered_map<std::string, function_t> &GetFunctions() const;
    const std::unordered_map<std::string, Operator *> &GetOperators() const;
    const std::unordered_map<std::string, IValue *> &GetVariables() const;
    const Operator *GetOperator(const std::string &) const;
    const function_t GetFunction(const std::string &) const;
    const IValue *GetVariable(const std::string &) const;
    const CharPair &GetBracketMarker() const;
    const CharPair &GetStringMarker() const;
    const CharPair &GetLazyEvalMarker() const;
    const CharPair &GetFunctionBrackets() const;
    const CharPair &GetSetMarkers() const;
    const CharPair &GetAccessorMarkers() const;
    char GetListSeperator() const;
    char GetDecimalSeperator() const;
    char GetFunctionParameterSeperator() const;
    char GetStringEscapeMarker() const;

private:
    std::unordered_map<std::string, function_t> functions;
    std::unordered_map<std::string, Operator *> operators;
    std::unordered_map<std::string, IValue *> variables;
    CharPair bracketMarker;
    CharPair stringMarker;
    CharPair lazyEvalMarker;
    CharPair functionBrackets;
    CharPair setMarkers;
    CharPair accessorMarkers;
    char listSeperator;
    char decimalSeperator;
    char functionParameterSeperator;
    char stringEscapeMarker;
};

class EvaluationContext
{
private:
    Config *config;

public:
    EvaluationContext(Config *config);

    Operator *GetOperator(const std::string &);
    function_t GetFunction(const std::string &);
    IValue *GetVariable(const std::string &);
};

namespace tokenizing
{
enum class TokenType
{
    String = 0x0000,
    Number = 0x0001,
    Identifier = 0x0002,
    Seperator = 0x0003,
    OpeningBracket = 0x0004,
    ClosingBracket = 0x0005,
    SetStart = 0x0006,
    SetEnd = 0x0007,
    AccessorStart = 0x0008,
    AccessorEnd = 0x0009,
    FunctionStart = 0x000A,
    FunctionEnd = 0x000B,
    LazyEvalSeperator = 0x000C,
    Operator = 0x1000,
};

std::ostream &operator<<(std::ostream &, TokenType);

class Token
{
private:
    TokenType type;
    std::string value;

public:
    Token();
    Token(TokenType type);
    Token(TokenType type, const std::string &value);

    TokenType GetType() const;
    const std::string &GetValue() const;
};

class Tokenizer
{
private:
    std::vector<std::string> sortedOperatorNames;

    std::vector<Token> tokens;
    char *data;
    int pos;
    int len;
    const Config *config;
    std::stack<char> bracketStack;
    bool lastWasWhiteSpace;
    Token buf;

    void InitStateMachine(const std::string &, const Config *);
    void ClearStateMachine();

    bool ReadNext();
    void SkipWhiteSpace();
    bool IsStartOfNumber(char);
    bool ReadString();
    bool IsStartOfIdentifier(char);
    bool ReadIdentifier();
    bool ReadLazyExpression();
    bool ReadNumber();
    bool IsAfterFunction();
    bool TryReadOperator();
    bool IsPartOfIdentifier(char);
    bool IsDigit(char);

public:
    Tokenizer();
    ~Tokenizer();

    bool Tokenize(const std::string &, const Config *);
    const std::vector<Token> &GetTokens() const;

    void UpdateOperatorNames();
};

enum class TokenizerError
{
    MissingBracket,
    ExtraClosingBracket,
    MismatchingBracket,
    InvalidChar,
    UnexpectedEndOfLazyExpression,
    UnexpectedEndOfStringExpression,
};

class TokenizerException : public util::Exception
{
public:
    TokenizerException(TokenizerError what, Tokenizer *);
};
} // namespace tokenizing

namespace parsing
{
class ExpressionBase
{
private:
    int argCount;

public:
    ExpressionBase(int);

    int GetArgCount() const;

    virtual IValue *Eval(const std::vector<IValue *> &args, EvaluationContext &) = 0;
};

class VariableExpression : public ExpressionBase
{
private:
    std::string name;

public:
    VariableExpression(const std::string &);

    IValue *Eval(const std::vector<IValue *> &args, EvaluationContext &);
};

class FunctionExpression : public ExpressionBase
{
private:
    std::string name;
    int args;

public:
    FunctionExpression(const Operator *);
    FunctionExpression(function_t, int args);
    FunctionExpression(const std::string &, int);

    IValue *Eval(const std::vector<IValue *> &args, EvaluationContext &);
};

class ValueExpression : public ExpressionBase
{
private:
    IValue *value;

public:
    ValueExpression(IValue *);
    ValueExpression(const std::string &);

    IValue *Eval(const std::vector<IValue *> &args, EvaluationContext &);
};

bool CreatePostFixExpression(const std::vector<tokenizing::Token> &tokens, std::vector<ExpressionBase *> &out, const Config &);
} // namespace parsing

class Calculator
{
private:
    Config config;

public:
    Config &GetConfig();
    const Config &GetConfig() const;
    void SetConfig(const Config &);

    IValue *Evaluate(const std::string &);
};

class ScriptingEngine
{
private:
    bool echo;
    bool useAns;
    bool loop;
    Calculator calculator;
    std::string workingDirectory;

    util::Channel in;
    util::Channel err;
    util::Channel out;
    util::Channel diagnostic;

    typedef void (ScriptingEngine::*action_t)(const std::string &arg);

    void Eval(const std::string &);
    void Tokenize(const std::string &);
    void Parse(const std::string &);
    void DefineVar(const std::string &);
    void DefineExp(const std::string &);
    void Undefine(const std::string &);
    void Quit(const std::string &);
    void Solve(const std::string &);
    void OpenErr(const std::string &);
    void OpenOut(const std::string &);
    void OpenIn(const std::string &);
    void ChangeDir(const std::string &);
    void SetEcho(const std::string &);
    void UseAns(const std::string &);
    void ClearOut(const std::string &);
    void ListFiles(const std::string &);
    void ClearVars(const std::string &);
    void ShowHelp(const std::string &);
    void SetDiagnosticOut(const std::string &);
    void HandleException(const std::exception &);
    void HandleException(const util::Exception &);
    int FindSimilarCommands(const std::string &command, std::vector<std::string> &out);
    void ListSimilarCommands(const std::string &command, std::vector<std::string> &out);
    void HandleUndefinedCommand(const std::string &command);
    void Define(const std::string &expression, bool compress);

    struct Action
    {
        std::string name;
        std::string alias;
        std::string description;
        action_t action;

        Action();
        Action(const std::string &name,
               const std::string &alias,
               const std::string &description,
               action_t action);

        bool HasAlias() const;
        bool HasDesciption() const;
    };

    std::unordered_map<std::string, Action> actions;
    std::vector<Action> uniqeActions;

public:
    ScriptingEngine();

    void LoadFile(const std::string &);
    void EvalScript(const std::string &);
    void EvalFromStdIn();
    void EvalStream(std::istream &);
};
} // namespace util
