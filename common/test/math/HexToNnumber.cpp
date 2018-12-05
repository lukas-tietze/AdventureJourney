#include "common/test/TestList.hpp"
#include "Test.hpp"
#include "data/Math.hpp"

int test::mathTest::TestHexToNumber()
{
    assert::AreEqual((uint8_t)0, util::HexToNumber('0'));
    assert::AreEqual((uint8_t)1, util::HexToNumber('1'));
    assert::AreEqual((uint8_t)2, util::HexToNumber('2'));
    assert::AreEqual((uint8_t)3, util::HexToNumber('3'));
    assert::AreEqual((uint8_t)4, util::HexToNumber('4'));
    assert::AreEqual((uint8_t)5, util::HexToNumber('5'));
    assert::AreEqual((uint8_t)6, util::HexToNumber('6'));
    assert::AreEqual((uint8_t)7, util::HexToNumber('7'));
    assert::AreEqual((uint8_t)8, util::HexToNumber('8'));
    assert::AreEqual((uint8_t)9, util::HexToNumber('9'));
    assert::AreEqual((uint8_t)10, util::HexToNumber('a'));
    assert::AreEqual((uint8_t)10, util::HexToNumber('A'));
    assert::AreEqual((uint8_t)11, util::HexToNumber('b'));
    assert::AreEqual((uint8_t)11, util::HexToNumber('B'));
    assert::AreEqual((uint8_t)12, util::HexToNumber('c'));
    assert::AreEqual((uint8_t)12, util::HexToNumber('C'));
    assert::AreEqual((uint8_t)13, util::HexToNumber('d'));
    assert::AreEqual((uint8_t)13, util::HexToNumber('D'));
    assert::AreEqual((uint8_t)14, util::HexToNumber('e'));
    assert::AreEqual((uint8_t)14, util::HexToNumber('E'));
    assert::AreEqual((uint8_t)15, util::HexToNumber('f'));
    assert::AreEqual((uint8_t)15, util::HexToNumber('F'));

    return 0;
}