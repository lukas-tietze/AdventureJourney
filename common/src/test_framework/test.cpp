#include <cstring>

#include "test.hpp"
#include "data/string.hpp"
#include <boost/stacktrace/stacktrace.hpp>

namespace
{
std::string make_msg(const std::string &msg, const std::string &customMsg)
{
    if (customMsg.empty())
        return util::format("Assert Failed: %s\nAt %s",
                            msg.c_str(),
                            util::to_string(boost::stacktrace::stacktrace()).c_str());
    else
        return util::format("Assert Failed: %s [%s]\nAt %s",
                            msg.c_str(),
                            customMsg.c_str(),
                            util::to_string(boost::stacktrace::stacktrace()).c_str());
}
} // namespace

assert::assert_exception::assert_exception(const std::string &msg, const std::string &customMsg) : util::exception(make_msg(msg, customMsg))
{
}

void assert::is_null(const void *ptr, const std::string &msg)
{
    if (ptr != nullptr)
    {
        throw assert::assert_exception("Pointer is not null!", msg);
    }
}

void assert::is_not_null(const void *ptr, const std::string &msg)
{
    if (ptr == nullptr)
    {
        throw assert::assert_exception("Pointer is null!", msg);
    }
}

void assert::fail(const std::string &msg)
{
    throw assert_exception("Assert failed!", msg);
}

void assert::is_true(bool x, const std::string &msg)
{
    if (!x)
    {
        throw assert_exception("Value is not true!", msg);
    }
}

void assert::is_false(bool x, const std::string &msg)
{
    if (x)
    {
        throw assert_exception("Value is not false!", msg);
    }
}