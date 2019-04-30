#include "Test.hpp"
#include "libCommon/test/TestList.hpp"
#include "Event.hpp"

namespace
{
constexpr int RES_X = 10;
constexpr int RES_Y = 100;
constexpr int RES_Z = 1000;
} // namespace

struct EventArgs
{
    int x, y, z;
};

void EventFunction(EventArgs &args)
{
    args.x = RES_X;
    args.y = RES_Y;
    args.z = RES_Z;
}

int test::eventTest::FunctionEvents()
{
    util::FunctionEvent<EventArgs> event;
    EventArgs args = {0, 0, 0};

    assert::AreEqual(0u, event.Size());
    event += &EventFunction;
    assert::AreEqual(1u, event.Size());

    event(args);

    assert::AreEqual(RES_X, args.x);
    assert::AreEqual(RES_Y, args.y);
    assert::AreEqual(RES_Z, args.z);

    assert::AreEqual(1u, event.Size());
    event -= &EventFunction;
    assert::AreEqual(0u, event.Size());

    args = {0, 0, 0};
    event(args);

    assert::AreEqual(0, args.x);
    assert::AreEqual(0, args.y);
    assert::AreEqual(0, args.z);
    assert::AreEqual(0u, event.Size());

    return 0;
}