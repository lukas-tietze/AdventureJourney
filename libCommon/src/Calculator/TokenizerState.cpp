#include "Calculator.hpp"

util::tokenizing::TokenizerState::TokenizerState(const std::string &data, int pos, const Token &lastToken) : data(data),
                                                                                                             pos(pos),
                                                                                                             lastToken(lastToken)
{
}

const char *util::tokenizing::TokenizerState::GetData() const
{
    return this->data;
}

int util::tokenizing::TokenizerState::GetPos() const
{
    return this->pos;
}

const util::tokenizing::Token *util::tokenizing::TokenizerState::GetLastToken() const
{
    return this->lastToken;
}
