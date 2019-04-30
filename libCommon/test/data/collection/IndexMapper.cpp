#include "Test.hpp"
#include "common/test/TestList.hpp"
#include "data/collection/IndexMapper.hpp"

#include <string>

int test::dataTest::collectionTest::TestIndexMapper()
{
    util::IndexMapper<std::string, int> mapper;

    assert::AreEqual(mapper["Null"], 0);
    assert::AreEqual(mapper["Eins"], 1);
    assert::AreEqual(mapper["Zwei"], 2);
    assert::AreEqual(mapper["Drei"], 3);
    assert::AreEqual(mapper["View"], 4);

    assert::AreEqual(mapper["View"], 4);
    assert::AreEqual(mapper["Drei"], 3);
    assert::AreEqual(mapper["Zwei"], 2);
    assert::AreEqual(mapper["Eins"], 1);
    assert::AreEqual(mapper["Null"], 0);

    mapper.Clear();

    assert::AreEqual(mapper["View"], 0);
    assert::AreEqual(mapper["Drei"], 1);
    assert::AreEqual(mapper["Zwei"], 2);
    assert::AreEqual(mapper["Eins"], 3);
    assert::AreEqual(mapper["Null"], 4);

    assert::AreEqual(mapper["Null"], 4);
    assert::AreEqual(mapper["Eins"], 3);
    assert::AreEqual(mapper["Zwei"], 2);
    assert::AreEqual(mapper["Drei"], 1);
    assert::AreEqual(mapper["View"], 0);

    return 0;
}