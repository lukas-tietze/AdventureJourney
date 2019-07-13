#pragma once

#include "Calculator.hpp"

namespace calculator
{
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
    OperatorAdd = Operator | static_cast<int>(OperatorType::Add),
    OperatorAddEq = Operator | static_cast<int>(OperatorType::AddEq),
    OperatorSub = Operator | static_cast<int>(OperatorType::Sub),
    OperatorSubEq = Operator | static_cast<int>(OperatorType::SubEq),
    OperatorMul = Operator | static_cast<int>(OperatorType::Mul),
    OperatorMulEq = Operator | static_cast<int>(OperatorType::MulEq),
    OperatorDiv = Operator | static_cast<int>(OperatorType::Div),
    OperatorDivEq = Operator | static_cast<int>(OperatorType::DivEq),
    OperatorEq = Operator | static_cast<int>(OperatorType::Eq),
    OperatorNot = Operator | static_cast<int>(OperatorType::Not),
    OperatorEqEq = Operator | static_cast<int>(OperatorType::EqEq),
    OperatorNotEq = Operator | static_cast<int>(OperatorType::NotEq),
    OperatorNotNot = Operator | static_cast<int>(OperatorType::NotNot),
    OperatorEqEqEq = Operator | static_cast<int>(OperatorType::EqEqEq),
    OperatorNotEqEq = Operator | static_cast<int>(OperatorType::NotEqEq),
    OperatorGt = Operator | static_cast<int>(OperatorType::Gt),
    OperatorGtEq = Operator | static_cast<int>(OperatorType::GtEq),
    OperatorGtGt = Operator | static_cast<int>(OperatorType::GtGt),
    OperatorGtGtEq = Operator | static_cast<int>(OperatorType::GtGtEq),
    OperatorLs = Operator | static_cast<int>(OperatorType::Ls),
    OperatorLsEq = Operator | static_cast<int>(OperatorType::LsEq),
    OperatorLsLs = Operator | static_cast<int>(OperatorType::LsLs),
    OperatorLsLsEq = Operator | static_cast<int>(OperatorType::LsLsEq),
    OperatorNeq = Operator | static_cast<int>(OperatorType::Neq),
    OperatorQe = Operator | static_cast<int>(OperatorType::Qe),
    OperatorQeQe = Operator | static_cast<int>(OperatorType::QeQe),
};

std::ostream &operator<<(std::ostream &, TokenType);

struct Token
{
    Token();
    Token(TokenType type);
    Token(TokenType type, int, int);

    TokenType type;
    int start;
    int len;
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

class Tokenizer
{
private:
    std::vector<Token> *tokens;
    const char *data;
    int pos;
    int len;
    const Config *config;
    std::stack<char> bracketStack;
    bool lastWasWhiteSpace;
    Token buf;

    void InitStateMachine(const std::string &, const Config &, std::vector<Token> &);
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
    void HandleError(TokenizerError);

public:
    Tokenizer();
    ~Tokenizer();

    bool Run(const std::string &, std::vector<Token> &, const Config &);
};

class TokenizerException : public util::Exception
{
public:
    TokenizerException(TokenizerError what, Tokenizer *);
};

bool Tokenize(const std::string &, std::vector<Token> &, const Config &);
} // namespace tokenizing
} // namespace calculator