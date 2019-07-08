#include "Calculator.hpp"

#include "data/String.hpp"

#include <algorithm>

namespace
{
constexpr char FUNCTION_BRACKET_MASK = (char)(1 << (sizeof(char) * 8 - 2));
} // namespace

calculator::tokenizing::Tokenizer::Tokenizer() : tokens(),
                                                 data(nullptr),
                                                 pos(0),
                                                 len(0),
                                                 config(nullptr),
                                                 bracketStack(),
                                                 lastWasWhiteSpace(false)
{
}

calculator::tokenizing::Tokenizer::~Tokenizer()
{
    this->ClearStateMachine();
}

const std::vector<calculator::tokenizing::Token> &calculator::tokenizing::Tokenizer::GetTokens() const
{
    return this->tokens;
}

void calculator::tokenizing::Tokenizer::InitStateMachine(const std::string &data, const Config *config)
{
    this->len = data.length();
    this->pos = 0;
    this->data = new char[this->len];
    this->config = config;
}

void calculator::tokenizing::Tokenizer::ClearStateMachine()
{
    if (this->data)
        delete[] this->data;

    this->bracketStack = std::stack<char>();
    this->tokens.clear();
}

bool calculator::tokenizing::Tokenizer::Tokenize(const std::string &data, const Config *config)
{
    this->ClearStateMachine();
    this->InitStateMachine(data, config);

    while (this->pos < this->len)
    {
        if (this->ReadNext())
        {
            this->tokens.push_back(this->buf);
        }
    }

    if (this->bracketStack.size() != 0)
    {
        throw TokenizerException(TokenizerError::MissingBracket, this);
    }
}

bool calculator::tokenizing::Tokenizer::ReadNext()
{
    this->lastWasWhiteSpace = false;

    if (std::isspace(this->data[this->pos]))
    {
        this->SkipWhiteSpace();
    }

    if (this->pos >= this->len)
    {
        return false;
    }

    auto c = this->data[this->pos];

    if (this->IsStartOfNumber(c))
    {
        return this->ReadNumber();
    }
    else if (c == this->config->GetStringMarker().opening)
    {
        return this->ReadString();
    }
    else if (this->IsStartOfIdentifier(c))
    {
        return this->ReadIdentifier();
    }
    else if (c == this->config->GetLazyEvalMarker().opening)
    {
        return this->ReadLazyExpression();
    }
    else if (c == this->config->GetFunctionBrackets().opening && this->IsAfterFunction())
    {
        auto functionName = this->tokens[this->tokens.size() - 1].GetValue();
        this->tokens.erase(--this->tokens.end());
        this->buf = Token(TokenType::FunctionStart, functionName);

        c |= FUNCTION_BRACKET_MASK;

        this->bracketStack.push(c);
        this->pos++;

        return true;
    }
    else if (c == this->config->GetBracketMarker().opening)
    {
        this->buf = Token(TokenType::OpeningBracket, std::string({c}));
        this->bracketStack.push(c);
        this->pos++;

        return true;
    }
    else if (c == this->config->GetBracketMarker().closing)
    {
        if (this->bracketStack.size() == 0)
        {
            throw TokenizerException(TokenizerError::ExtraClosingBracket, this);
        }

        this->pos++;
        auto last = this->bracketStack.top();
        this->bracketStack.pop();
        TokenType type;

        if ((last & FUNCTION_BRACKET_MASK) != 0)
        {
            last = (char)(last & ~FUNCTION_BRACKET_MASK);
            type = TokenType::FunctionEnd;

            if (last != this->config->GetFunctionBrackets().closing)
            {
                throw TokenizerException(TokenizerError::MismatchingBracket, this);
            }
        }
        else
        {
            type = TokenType::ClosingBracket;

            if (last != this->config->GetBracketMarker().closing)
            {
                throw TokenizerException(TokenizerError::MismatchingBracket, this);
            }
        }

        this->buf = Token(type, std::string({c}));
    }
    else if (c == this->config->GetSetMarkers().opening)
    {
        this->pos++;
        return new Token(TokenType::SetStart);
    }
    else if (c == this->config->GetSetMarkers().closing)
    {
        this->pos++;
        return new Token(TokenType::SetEnd);
    }
    else if (c == this->config->GetAccessorMarkers().opening)
    {
        this->pos++;
        return new Token(TokenType::AccessorStart);
    }
    else if (c == this->config->GetAccessorMarkers().closing)
    {
        this->pos++;
        return new Token(TokenType::AccessorEnd);
    }
    else if (c == this->config->GetListSeperator())
    {
        this->pos++;
        return new Token(TokenType::Seperator, std::string({c}));
    }
    else if (this->TryReadOperator())
    {
        return true;
    }
    else
    {
        throw TokenizerException(TokenizerError::InvalidChar, this);
    }
}

bool calculator::tokenizing::Tokenizer::ReadLazyExpression()
{
    auto start = ++this->pos;

    while (this->data[this->pos] != this->config->GetLazyEvalMarker().closing)
    {
        if (this->pos >= this->len)
        {
            throw TokenizerException(TokenizerError::UnexpectedEndOfLazyExpression, this);
        }

        pos++;
    }

    pos++;

    this->buf = Token(TokenType::LazyEvalSeperator, std::string(this->data + start, pos - start - 1));
}

bool calculator::tokenizing::Tokenizer::TryReadOperator()
{
    char opc[3] = {
        this->data[this->pos + 0],
        this->pos + 1 < this->len ? this->data[this->pos + 1] : 0,
        this->pos + 2 < this->len ? this->data[this->pos + 2] : 0,
    };

    TokenType res;

    switch (opc[0])
    {
    case '+':
        res = opc[1] == '='
                  ? calculator::tokenizing::TokenType::OperatorAddEq
                  : calculator::tokenizing::TokenType::OperatorAdd;
        break;
    case '-':
        res = opc[1] == '='
                  ? calculator::tokenizing::TokenType::OperatorSub
                  : calculator::tokenizing::TokenType::OperatorSubEq;
        break;
    case '*':
        res = opc[1] == '='
                  ? calculator::tokenizing::TokenType::OperatorMul
                  : calculator::tokenizing::TokenType::OperatorMulEq;
        break;
    case '/':
        res = opc[1] == '='
                  ? calculator::tokenizing::TokenType::OperatorDiv
                  : calculator::tokenizing::TokenType::OperatorDivEq;
        break;
    case '=':
        if (opc[1] == '=')
            res = opc[2] == '='
                      ? calculator::tokenizing::TokenType::OperatorEqEqEq
                      : calculator::tokenizing::TokenType::OperatorEqEq;
        else
            calculator::tokenizing::TokenType::OperatorEq;
        break;
    case '!':
        if (opc[1] == '=')
            res = opc[2] == '='
                      ? calculator::tokenizing::TokenType::OperatorNotEqEq
                      : calculator::tokenizing::TokenType::OperatorNotEq;
        else if (opc[1] == '!')
            res = calculator::tokenizing::TokenType::OperatorNotNot;
        else
            res = calculator::tokenizing::TokenType::OperatorNot;
        break;
    case '>':
        if (opc[1] == '>')
            res = opc[2] == '='
                      ? calculator::tokenizing::TokenType::OperatorGtGtEq
                      : calculator::tokenizing::TokenType::OperatorGtGt;
        else if (opc[1] == '=')
            res = calculator::tokenizing::TokenType::OperatorGtEq;
        else
            res = calculator::tokenizing::TokenType::OperatorGt;
        break;
    case '<':
        if (opc[1] == '<')
            res = opc[2] == '='
                      ? calculator::tokenizing::TokenType::OperatorLsLsEq
                      : calculator::tokenizing::TokenType::OperatorLsLs;
        else if (opc[1] == '=')
            res = calculator::tokenizing::TokenType::OperatorLsEq;
        else if (opc[1] == '>')
            res = calculator::tokenizing::TokenType::OperatorNeq;
        else
            res = calculator::tokenizing::TokenType::OperatorLs;
        break;
    case '?':
        res = opc[1] == '?'
                  ? calculator::tokenizing::TokenType::OperatorQeQe
                  : calculator::tokenizing::TokenType::OperatorQe;
        break;
    default:
        return false;
    }

    this->buf = Token(res);

    switch (res)
    {
    case calculator::tokenizing::TokenType::OperatorAdd:
    case calculator::tokenizing::TokenType::OperatorSub:
    case calculator::tokenizing::TokenType::OperatorMul:
    case calculator::tokenizing::TokenType::OperatorDiv:
    case calculator::tokenizing::TokenType::OperatorEq:
    case calculator::tokenizing::TokenType::OperatorNot:
    case calculator::tokenizing::TokenType::OperatorGt:
    case calculator::tokenizing::TokenType::OperatorLs:
    case calculator::tokenizing::TokenType::OperatorNeq:
    case calculator::tokenizing::TokenType::OperatorQe:
        this->pos++;
        break;
    case calculator::tokenizing::TokenType::OperatorAddEq:
    case calculator::tokenizing::TokenType::OperatorSubEq:
    case calculator::tokenizing::TokenType::OperatorMulEq:
    case calculator::tokenizing::TokenType::OperatorDivEq:
    case calculator::tokenizing::TokenType::OperatorEqEq:
    case calculator::tokenizing::TokenType::OperatorNotEq:
    case calculator::tokenizing::TokenType::OperatorGtEq:
    case calculator::tokenizing::TokenType::OperatorGtGt:
    case calculator::tokenizing::TokenType::OperatorLsEq:
    case calculator::tokenizing::TokenType::OperatorLsLs:
    case calculator::tokenizing::TokenType::OperatorQeQe:
    case calculator::tokenizing::TokenType::OperatorNotNot:
        this->pos += 2;
        break;
    case calculator::tokenizing::TokenType::OperatorEqEqEq:
    case calculator::tokenizing::TokenType::OperatorNotEqEq:
    case calculator::tokenizing::TokenType::OperatorGtGtEq:
    case calculator::tokenizing::TokenType::OperatorLsLsEq:
        this->pos += 3;
    };

    return true;
}

bool calculator::tokenizing::Tokenizer::ReadIdentifier()
{
    auto readStart = this->pos;

    do
    {
        ++this->pos;
    } while (this->pos < this->len && this->IsPartOfIdentifier(this->data[this->pos]));

    return new Token(TokenType::Identifier, std::string(this->data + readStart, this->pos - readStart));
}

bool calculator::tokenizing::Tokenizer::ReadString()
{
    std::string sb;
    auto escaped = false;

    while (++this->pos < this->len)
    {
        auto c = this->data[this->pos];

        if (escaped)
        {
            sb.push_back(util::Escape(c));
            escaped = false;
        }
        else if (c == this->config->GetStringEscapeMarker())
        {
            escaped = true;
        }
        else if (c == this->config->GetStringMarker().closing)
        {
            this->pos++;
            break;
        }
        else
        {
            sb.push_back(c);
        }
    }

    return new Token(TokenType::String, sb);
}

bool calculator::tokenizing::Tokenizer::ReadNumber()
{
    auto decSeperatorRead = false;
    auto prefixRead = false;
    auto readStart = this->pos;

    while (this->pos < this->len)
    {
        auto c = this->data[this->pos];

        if (!this->IsDigit(c))
        {
            if (c == this->config->GetDecimalSeperator() && !decSeperatorRead)
            {
                decSeperatorRead = true;
            }
            else if (c != '-' || prefixRead)
            {
                break;
            }
        }

        prefixRead = true;

        this->pos++;
    }

    return new Token(TokenType::Number, std::string(this->data + readStart, this->pos - readStart));
}

void calculator::tokenizing::Tokenizer::SkipWhiteSpace()
{
    auto readStart = this->pos;

    while (this->pos < this->len && std::isspace(this->data[this->pos]))
    {
        this->pos++;
    }

    this->lastWasWhiteSpace = true;
}

bool calculator::tokenizing::Tokenizer::IsAfterFunction()
{
    return this->tokens.size() != 0 && this->tokens[this->tokens.size() - 1].GetType() == TokenType::Identifier;
}

bool calculator::tokenizing::Tokenizer::IsStartOfIdentifier(char c)
{
    return c >= 'a' && c <= 'z' ||
           c >= 'A' && c <= 'Z' ||
           c == '_';
}

bool calculator::tokenizing::Tokenizer::IsPartOfIdentifier(char c)
{
    return c >= 'a' && c <= 'z' ||
           c >= 'A' && c <= 'Z' ||
           c >= '0' && c <= '9' ||
           c == '_';
}

bool calculator::tokenizing::Tokenizer::IsDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool calculator::tokenizing::Tokenizer::IsStartOfNumber(char c)
{
    return this->IsDigit(c) || c == this->config->GetDecimalSeperator() ||
           (c == '-' && (this->tokens.size() == 0 ||
                         (this->tokens.size() > 0 && this->tokens[this->tokens.size() - 1].GetType() == TokenType::OpeningBracket)));
}
