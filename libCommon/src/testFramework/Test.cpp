#include <cstring>
#include <string>
#include <boost/stacktrace/stacktrace.hpp>

#include "data/String.hpp"
#include "Test.hpp"

namespace
{
std::string make_msg(const std::string &msg, const std::string &customMsg)
{
    if (customMsg.empty())
        return util::Format("Assert Failed: %s\n",
                            msg.c_str());
    else
        return util::Format("Assert Failed: %s [%s]\n",
                            msg.c_str(),
                            customMsg.c_str());
}
} // namespace

assert::AssertException::AssertException(const std::string &msg, const std::string &customMsg) : util::Exception(make_msg(msg, customMsg))
{
}

void assert::IsNull(const void *ptr, const std::string &msg)
{
    if (ptr != nullptr)
    {
        throw assert::AssertException("Pointer is not null!", msg);
    }
}

void assert::IsNotNull(const void *ptr, const std::string &msg)
{
    if (ptr == nullptr)
    {
        throw assert::AssertException("Pointer is null!", msg);
    }
}

void assert::Fail(const std::string &msg)
{
    throw AssertException("Assert failed!", msg);
}

void assert::IsTrue(bool x, const std::string &msg)
{
    if (!x)
    {
        throw AssertException("Value is not true!", msg);
    }
}

void assert::IsFalse(bool x, const std::string &msg)
{
    if (x)
    {
        throw AssertException("Value is not false!", msg);
    }
}

void assert::AreEqual(const char *x, const std::string &y, const std::string &msg)
{
    if (std::strcmp(x, y.c_str()) != 0)
    {
        throw AssertException("Expected <" + util::ToString(x) + ">, got <" + util::ToString(y) + ">!", msg);
    }
}