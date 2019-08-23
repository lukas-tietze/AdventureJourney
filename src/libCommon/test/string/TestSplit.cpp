#include "Test.hpp"
#include "libCommon/test/TestList.hpp"
#include "data/String.hpp"

int test::stringTest::SplitSpace()
{
    std::vector<std::string> parts;

    parts = util::Split(" a\tb 1c2\n3   ##", true);

    assert::AreEqual((size_t)3, parts.size());
    assert::AreEqual(std::string("a\tb"), parts[0]);
    assert::AreEqual(std::string("1c2\n3"), parts[1]);
    assert::AreEqual(std::string("##"), parts[2]);

    return 0;
}

int test::stringTest::SplitCustomChar()
{
    std::vector<std::string> parts;

    // parts = util::Split("__ab__cd ef_gh____", '_');

    parts = util::Split("__ab_cd ef_gh_ ___", '_', true);

    assert::AreEqual((size_t)4, parts.size());
    assert::AreEqual(std::string("ab"), parts[0]);
    assert::AreEqual(std::string("cd ef"), parts[1]);
    assert::AreEqual(std::string("gh"), parts[2]);
    assert::AreEqual(std::string(" "), parts[3]);

    return 0;
}

int test::stringTest::SplitMultipleChars()
{
    auto parts = util::Split(" ,ab cd_ef,gh_  ,ij", " ,_");

    return 0;
}

int test::stringTest::SplitFunction()
{
    return 0;
}
