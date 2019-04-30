#include "Test.hpp"
#include "libCommon/test/TestList.hpp"
#include "data/String.hpp"

int test::stringTest::Justification()
{
    auto res = util::Justify("a aa bbb cc cdddde e", 4);

    assert::AreEqual("a aa", res[0]);
    assert::AreEqual("bbb", res[1]);
    assert::AreEqual("cc c", res[2]);
    assert::AreEqual("dddd", res[3]);
    assert::AreEqual("e e", res[4]);

    res = util::Justify("a\nb\n\n\nc", 4);

    assert::AreEqual("a", res[0]);
    assert::AreEqual("b", res[1]);
    assert::AreEqual("", res[2]);
    assert::AreEqual("", res[3]);
    assert::AreEqual("c", res[4]);
}