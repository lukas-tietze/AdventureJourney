#include "Test.hpp"
#include "common/test/TestList.hpp"
#include "data/String.hpp"

int test::stringTest::Strip()
{
    assert::AreEqual(std::string("abc"), util::Strip(" abc"));
    assert::AreEqual(std::string("abc"), util::Strip(" abc "));
    assert::AreEqual(std::string("abc"), util::Strip("\tabc\t"));
    assert::AreEqual(std::string("abc"), util::Strip("\nabc\n"));
    assert::AreEqual(std::string("abc"), util::Strip("   abc    "));
    assert::AreEqual(std::string("abc"), util::Strip(" \t\nabc\n\n   \t"));

    return 0;
}

int test::stringTest::StripFront()
{
    assert::AreEqual(std::string("abc "), util::StripFront(" abc "));
    assert::AreEqual(std::string("abc "), util::StripFront("\nabc "));
    assert::AreEqual(std::string("abc "), util::StripFront("\tabc "));
    assert::AreEqual(std::string("abc    "), util::StripFront("   abc    "));
    assert::AreEqual(std::string("abc\n\n   \t"), util::StripFront(" \t\nabc\n\n   \t"));

    return 0;
}

int test::stringTest::StripBack()
{
    assert::AreEqual(std::string(" abc"), util::StripBack(" abc "));
    assert::AreEqual(std::string(" abc"), util::StripBack(" abc\n"));
    assert::AreEqual(std::string(" abc"), util::StripBack(" abc\t"));
    assert::AreEqual(std::string("   abc"), util::StripBack("   abc    "));
    assert::AreEqual(std::string(" \t\nabc"), util::StripBack(" \t\nabc\n\n   \t"));

    return 0;
}

int test::stringTest::StripInplace()
{
    assert::AreEqual(std::string("abc"), util::Strip(" abc"));
    assert::AreEqual(std::string("abc"), util::Strip(" abc "));
    assert::AreEqual(std::string("abc"), util::Strip("\tabc\t"));
    assert::AreEqual(std::string("abc"), util::Strip("\nabc\n"));
    assert::AreEqual(std::string("abc"), util::Strip("   abc    "));
    assert::AreEqual(std::string("abc"), util::Strip(" \t\nabc\n\n   \t"));

    return 0;
}

int test::stringTest::StripFrontInplace()
{
    assert::AreEqual(std::string("abc "), util::StripFront(" abc "));
    assert::AreEqual(std::string("abc "), util::StripFront("\nabc "));
    assert::AreEqual(std::string("abc "), util::StripFront("\tabc "));
    assert::AreEqual(std::string("abc    "), util::StripFront("   abc    "));
    assert::AreEqual(std::string("abc\n\n   \t"), util::StripFront(" \t\nabc\n\n   \t"));

    return 0;
}

int test::stringTest::StripBackInplace()
{
    assert::AreEqual(std::string(" abc"), util::StripBack(" abc "));
    assert::AreEqual(std::string(" abc"), util::StripBack(" abc\n"));
    assert::AreEqual(std::string(" abc"), util::StripBack(" abc\t"));
    assert::AreEqual(std::string("   abc"), util::StripBack("   abc    "));
    assert::AreEqual(std::string(" \t\nabc"), util::StripBack(" \t\nabc\n\n   \t"));

    return 0;
}