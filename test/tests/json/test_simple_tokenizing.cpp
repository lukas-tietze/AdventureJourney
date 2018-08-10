#include <cstdio>

#include "test.hpp"
#include "json.hpp"

int test::json::test_simple_tokenizing()
{
    std::string text = "{\"foo\": 3}";

    ::json::tokenizer t;

    auto tokens = t.tokenize(text);

    for (const auto &token : tokens)
    {
        util::printr(token);
    }

    return 0;
}