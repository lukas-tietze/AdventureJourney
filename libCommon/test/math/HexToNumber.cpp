#include "common/test/TestList.hpp"
#include "Test.hpp"
#include "data/Math.hpp"

int test::mathTest::TestHexToNumber()
{
    assert::AreEqual(0, static_cast<int>(util::HexToNumber('0')));
    assert::AreEqual(1, static_cast<int>(util::HexToNumber('1')));
    assert::AreEqual(2, static_cast<int>(util::HexToNumber('2')));
    assert::AreEqual(3, static_cast<int>(util::HexToNumber('3')));
    assert::AreEqual(4, static_cast<int>(util::HexToNumber('4')));
    assert::AreEqual(5, static_cast<int>(util::HexToNumber('5')));
    assert::AreEqual(6, static_cast<int>(util::HexToNumber('6')));
    assert::AreEqual(7, static_cast<int>(util::HexToNumber('7')));
    assert::AreEqual(8, static_cast<int>(util::HexToNumber('8')));
    assert::AreEqual(9, static_cast<int>(util::HexToNumber('9')));
    assert::AreEqual(10, static_cast<int>(util::HexToNumber('a')));
    assert::AreEqual(10, static_cast<int>(util::HexToNumber('A')));
    assert::AreEqual(11, static_cast<int>(util::HexToNumber('b')));
    assert::AreEqual(11, static_cast<int>(util::HexToNumber('B')));
    assert::AreEqual(12, static_cast<int>(util::HexToNumber('c')));
    assert::AreEqual(12, static_cast<int>(util::HexToNumber('C')));
    assert::AreEqual(13, static_cast<int>(util::HexToNumber('d')));
    assert::AreEqual(13, static_cast<int>(util::HexToNumber('D')));
    assert::AreEqual(14, static_cast<int>(util::HexToNumber('e')));
    assert::AreEqual(14, static_cast<int>(util::HexToNumber('E')));
    assert::AreEqual(15, static_cast<int>(util::HexToNumber('f')));
    assert::AreEqual(15, static_cast<int>(util::HexToNumber('F')));

    assert::AreEqual(16, static_cast<int>(util::HexToNumber('1', '0')));

    return 0;
}