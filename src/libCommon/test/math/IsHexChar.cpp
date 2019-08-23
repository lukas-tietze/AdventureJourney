#include "libCommon/test/TestList.hpp"
#include "data/Math.hpp"
#include "Test.hpp"

int test::mathTest::TestIsHexChar()
{
    //vollstämndige positiv-Tests
    assert::IsTrue(util::IsHexChar('0'));
    assert::IsTrue(util::IsHexChar('1'));
    assert::IsTrue(util::IsHexChar('2'));
    assert::IsTrue(util::IsHexChar('3'));
    assert::IsTrue(util::IsHexChar('4'));
    assert::IsTrue(util::IsHexChar('5'));
    assert::IsTrue(util::IsHexChar('6'));
    assert::IsTrue(util::IsHexChar('7'));
    assert::IsTrue(util::IsHexChar('8'));
    assert::IsTrue(util::IsHexChar('9'));
    assert::IsTrue(util::IsHexChar('a'));
    assert::IsTrue(util::IsHexChar('A'));
    assert::IsTrue(util::IsHexChar('b'));
    assert::IsTrue(util::IsHexChar('B'));
    assert::IsTrue(util::IsHexChar('c'));
    assert::IsTrue(util::IsHexChar('C'));
    assert::IsTrue(util::IsHexChar('d'));
    assert::IsTrue(util::IsHexChar('D'));
    assert::IsTrue(util::IsHexChar('e'));
    assert::IsTrue(util::IsHexChar('E'));
    assert::IsTrue(util::IsHexChar('f'));
    assert::IsTrue(util::IsHexChar('F'));

    //einige negativ-tests
    assert::IsFalse(util::IsHexChar('X'));
    assert::IsFalse(util::IsHexChar('r'));
    assert::IsFalse(util::IsHexChar('-'));
    assert::IsFalse(util::IsHexChar('#'));
    assert::IsFalse(util::IsHexChar('t'));
    assert::IsFalse(util::IsHexChar('Q'));
    assert::IsFalse(util::IsHexChar('V'));
    assert::IsFalse(util::IsHexChar('G'));
    assert::IsFalse(util::IsHexChar('g'));
    assert::IsFalse(util::IsHexChar('+'));
    assert::IsFalse(util::IsHexChar('_'));

    return 0;
}