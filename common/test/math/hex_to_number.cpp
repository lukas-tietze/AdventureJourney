#include "common/test/test_list.hpp"
#include "test.hpp"
#include "data/math.hpp"

int test::math_test::test_hex_to_number()
{
    assert::are_equal((uint8_t)0, util::hexToNumber('0'));
    assert::are_equal((uint8_t)1, util::hexToNumber('1'));
    assert::are_equal((uint8_t)2, util::hexToNumber('2'));
    assert::are_equal((uint8_t)3, util::hexToNumber('3'));
    assert::are_equal((uint8_t)4, util::hexToNumber('4'));
    assert::are_equal((uint8_t)5, util::hexToNumber('5'));
    assert::are_equal((uint8_t)6, util::hexToNumber('6'));
    assert::are_equal((uint8_t)7, util::hexToNumber('7'));
    assert::are_equal((uint8_t)8, util::hexToNumber('8'));
    assert::are_equal((uint8_t)9, util::hexToNumber('9'));
    assert::are_equal((uint8_t)10, util::hexToNumber('a'));
    assert::are_equal((uint8_t)10, util::hexToNumber('A'));
    assert::are_equal((uint8_t)11, util::hexToNumber('b'));
    assert::are_equal((uint8_t)11, util::hexToNumber('B'));
    assert::are_equal((uint8_t)12, util::hexToNumber('c'));
    assert::are_equal((uint8_t)12, util::hexToNumber('C'));
    assert::are_equal((uint8_t)13, util::hexToNumber('d'));
    assert::are_equal((uint8_t)13, util::hexToNumber('D'));
    assert::are_equal((uint8_t)14, util::hexToNumber('e'));
    assert::are_equal((uint8_t)14, util::hexToNumber('E'));
    assert::are_equal((uint8_t)15, util::hexToNumber('f'));
    assert::are_equal((uint8_t)15, util::hexToNumber('F'));

    return 0;
}