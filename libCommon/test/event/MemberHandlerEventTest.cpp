#include "Test.hpp"
#include "common/test/TestList.hpp"
#include "Event.hpp"

namespace
{
constexpr int RES_X = 10;
constexpr int RES_Y = 100;
constexpr int RES_Z = 1000;

struct EventArgs
{
    int x, y, z;
};

struct EventHandler
{
    int id;

    void HandleSomeEvent(EventArgs &args)
    {
        args.x = RES_X + id;
        args.y = RES_Y + id;
        args.z = RES_Z + id;
    }
};
} // namespace

int test::eventTest::MemberHandlerEvents()
{
    util::MemberEvent<EventArgs> event;
    EventHandler handler = {1};
    auto member_handler = util::MakeMemberHandler(&handler, &EventHandler::HandleSomeEvent);
    EventArgs args = {0, 0, 0};

    assert::AreEqual(0u, event.Size());
    event += member_handler;
    assert::AreEqual(1u, event.Size());

    event(args);

    assert::AreEqual(RES_X + handler.id, args.x);
    assert::AreEqual(RES_Y + handler.id, args.y);
    assert::AreEqual(RES_Z + handler.id, args.z);

    assert::AreEqual(1u, event.Size());
    event -= member_handler;
    assert::AreEqual(0u, event.Size());

    args = {0, 0, 0};
    event(args);

    assert::AreEqual(0, args.x);
    assert::AreEqual(0, args.y);
    assert::AreEqual(0, args.z);
    assert::AreEqual(0u, event.Size());

    return 0;
}