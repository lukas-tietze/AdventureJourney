#include "data/json.hpp"
#include "data/string.hpp"

const std::string create_tokenizer_state_info(const json::tokenizer &t)
{
    auto pos = t.get_pos();
    auto len = t.get_length();
    auto reqEnd = pos + 10;
    auto cut = std::string(t.get_data() + pos, len < reqEnd ? len : reqEnd);

    return util::format("At %i ...%s...", pos, cut.c_str());
}

json::tokenizer_exception::tokenizer_exception() : util::exception("Undefined tokenizer exception!")
{
}

json::tokenizer_exception::tokenizer_exception(const tokenizer &t) : util::exception("Undefined exception! " + create_tokenizer_state_info(t))
{
}

json::tokenizer_exception::tokenizer_exception(const tokenizer &t, const std::string &message) : util::exception(message + create_tokenizer_state_info(t))
{
}