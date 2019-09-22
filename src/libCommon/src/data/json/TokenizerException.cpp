#include <cmath>
#include <algorithm>

#include "libCommon/data/Json.hpp"
#include "libCommon/data/String.hpp"

namespace
{
const std::string CreateTokenizerStateInfo(const json::Tokenizer &t)
{
    auto pos = t.GetPos();
    auto len = std::min(static_cast<int>(t.GetLength() - pos - 1), 20);
    auto cut = std::string(t.GetData() + pos, len);

    return util::Format(" At %i %s%s%s",
                        pos,
                        pos == 0 ? "" : "...",
                        cut.c_str(),
                        len < 20 ? "" : "...");
}
} // namespace

json::TokenizerException::TokenizerException() : util::Exception("Undefined tokenizer exception!")
{
}

json::TokenizerException::TokenizerException(const Tokenizer &t) : util::Exception("Undefined exception!" + CreateTokenizerStateInfo(t))
{
}

json::TokenizerException::TokenizerException(const Tokenizer &t, const std::string &message) : util::Exception(message + CreateTokenizerStateInfo(t))
{
}