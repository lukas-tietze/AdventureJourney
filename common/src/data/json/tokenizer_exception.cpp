#include <cmath>

#include "data/json.hpp"
#include "data/string.hpp"

namespace
{
const std::string create_tokenizer_state_info(const json::tokenizer &t)
{
    auto pos = t.get_pos();
    auto len = std::min(t.get_length() - pos - 1, 20);
    auto cut = std::string(t.get_data() + pos, len);

    return util::format(" At %i %s%s%s",
                        pos,
                        pos == 0 ? "" : "...",
                        cut.c_str(),
                        len < 20 ? "" : "...");
}
} // namespace

json::tokenizer_exception::tokenizer_exception() : util::exception("Undefined tokenizer exception!")
{
}

json::tokenizer_exception::tokenizer_exception(const tokenizer &t) : util::exception("Undefined exception!" + create_tokenizer_state_info(t))
{
}

json::tokenizer_exception::tokenizer_exception(const tokenizer &t, const std::string &message) : util::exception(message + create_tokenizer_state_info(t))
{
}