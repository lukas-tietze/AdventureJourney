#include "Calculator.hpp"

#include "data/String.hpp"

#include <algorithm>

namespace
{
constexpr char FUNCTION_BRACKET_MASK = (char)(1 << (sizeof(char) * 8 - 2));

struct OperatorNameComparer
{
    int operator()(const std::string &a, const std::string &b)
    {
        int res = 0;

        for (size_t i = 0; i < a.length() && i < b.length() && res == 0; i++)
        {
            res = a[i] - b[i];
        }

        if (res == 0)
            res = a.length() - b.length();

        return res;
    }
};

} // namespace

util::tokenizing::Tokenizer::Tokenizer() : tokens(),
                                           data(nullptr),
                                           pos(0),
                                           len(0),
                                           config(nullptr),
                                           bracketStack(),
                                           lastWasWhiteSpace(false)
{
}

util::tokenizing::Tokenizer::~Tokenizer()
{
    this->ClearStateMachine();
}

void util::tokenizing::Tokenizer::UpdateOperatorNames()
{
    this->sortedOperatorNames.clear();
    this->sortedOperatorNames.reserve(this->config->GetOperators().size());

    for (const auto kvp : this->config->GetOperators())
        this->sortedOperatorNames.push_back(kvp.first);

    std::sort(this->sortedOperatorNames.begin(), this->sortedOperatorNames.end(), OperatorNameComparer());
}

const std::vector<util::tokenizing::Token> &util::tokenizing::Tokenizer::GetTokens() const
{
    return this->tokens;
}

void util::tokenizing::Tokenizer::InitStateMachine(const std::string &data, const Config *config)
{
    this->len = data.length();
    this->pos = 0;
    this->data = new char[this->len];
    this->config = config;
}

void util::tokenizing::Tokenizer::ClearStateMachine()
{
    if (this->data)
        delete[] this->data;

    this->bracketStack = std::stack<char>();
    this->tokens.clear();
}

bool util::tokenizing::Tokenizer::Tokenize(const std::string &data, const Config *config)
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
        throw MissingBracketException(this);
    }
}

bool util::tokenizing::Tokenizer::ReadNext()
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
            throw ExtraClosingBracketException(this);
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
                throw MismatchingBracketException(this);
            }
        }
        else
        {
            type = TokenType::ClosingBracket;

            if (last != this->config->GetBracketMarker().closing)
            {
                throw MismatchingBracketException(this);
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
        throw InvalidCharException(this);
    }
}

bool util::tokenizing::Tokenizer::ReadLazyExpression()
{
    auto start = ++this->pos;

    while (this->data[this->pos] != this->config->GetLazyEvalMarker().closing)
    {
        if (this->pos >= this->len)
        {
            throw UnexpectedEndOfLazyExpressionException(this);
        }

        pos++;
    }

    pos++;

    this->buf = Token(TokenType::LazyEvalSeperator, std::string(this->data + start, pos - start - 1));
}

bool util::tokenizing::Tokenizer::TryReadOperator()
{
    char opc[3] = {this->data[this->pos + 0],
                   this->data[this->pos + 1],
                   this->data[this->pos + 2]};

    return true;
}

bool util::tokenizing::Tokenizer::ReadIdentifier()
{
    auto readStart = this->pos;

    do
    {
        ++this->pos;
    } while (this->pos < this->len && this->IsPartOfIdentifier(this->data[this->pos]));

    return new Token(TokenType::Identifier, std::string(this->data + readStart, this->pos - readStart));
}

bool util::tokenizing::Tokenizer::ReadString()
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

bool util::tokenizing::Tokenizer::ReadNumber()
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

void util::tokenizing::Tokenizer::SkipWhiteSpace()
{
    auto readStart = this->pos;

    while (this->pos < this->len && std::isspace(this->data[this->pos]))
    {
        this->pos++;
    }

    this->lastWasWhiteSpace = true;
}

bool util::tokenizing::Tokenizer::IsAfterFunction()
{
    return this->tokens.size() != 0 && this->tokens[this->tokens.size() - 1].GetType() == TokenType::Identifier;
}

bool util::tokenizing::Tokenizer::IsStartOfIdentifier(char c)
{
    return c >= 'a' && c <= 'z' ||
           c >= 'A' && c <= 'Z' ||
           c == '_';
}

bool util::tokenizing::Tokenizer::IsPartOfIdentifier(char c)
{
    return c >= 'a' && c <= 'z' ||
           c >= 'A' && c <= 'Z' ||
           c >= '0' && c <= '9' ||
           c == '_';
}

bool util::tokenizing::Tokenizer::IsDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool util::tokenizing::Tokenizer::IsStartOfNumber(char c)
{
    return this->IsDigit(c) || c == this->config->GetDecimalSeperator() ||
           (c == '-' && (this->tokens.size() == 0 ||
                         (this->tokens.size() > 0 && this->tokens[this->tokens.size() - 1].GetType() == TokenType::OpeningBracket)));
}
