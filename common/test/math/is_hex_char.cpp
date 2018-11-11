#include "common/test/test_list.hpp"
#include "data/math.hpp"
#include "test.hpp"

int test::math_test::test_is_hex_char()
{
    //vollstämndige positiv-Tests
    assert::is_true(util::is_hex_char('0'));
    assert::is_true(util::is_hex_char('1'));
    assert::is_true(util::is_hex_char('2'));
    assert::is_true(util::is_hex_char('3'));
    assert::is_true(util::is_hex_char('4'));
    assert::is_true(util::is_hex_char('5'));
    assert::is_true(util::is_hex_char('6'));
    assert::is_true(util::is_hex_char('7'));
    assert::is_true(util::is_hex_char('8'));
    assert::is_true(util::is_hex_char('9'));
    assert::is_true(util::is_hex_char('a'));
    assert::is_true(util::is_hex_char('A'));
    assert::is_true(util::is_hex_char('b'));
    assert::is_true(util::is_hex_char('B'));
    assert::is_true(util::is_hex_char('c'));
    assert::is_true(util::is_hex_char('C'));
    assert::is_true(util::is_hex_char('d'));
    assert::is_true(util::is_hex_char('D'));
    assert::is_true(util::is_hex_char('e'));
    assert::is_true(util::is_hex_char('E'));
    assert::is_true(util::is_hex_char('f'));
    assert::is_true(util::is_hex_char('F'));

    //einige negativ-tests
    assert::is_false(util::is_hex_char('X'));
    assert::is_false(util::is_hex_char('r'));
    assert::is_false(util::is_hex_char('-'));
    assert::is_false(util::is_hex_char('#'));
    assert::is_false(util::is_hex_char('t'));
    assert::is_false(util::is_hex_char('Q'));
    assert::is_false(util::is_hex_char('V'));
    assert::is_false(util::is_hex_char('G'));
    assert::is_false(util::is_hex_char('g'));
    assert::is_false(util::is_hex_char('+'));
    assert::is_false(util::is_hex_char('_'));

    return 0;
}