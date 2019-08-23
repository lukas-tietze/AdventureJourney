#include "Test.hpp"
#include "libCommon/test/TestList.hpp"
#include "Event.hpp"

namespace
{
struct EventArgs
{
    int x, y, z;
};

void StaticEventFunction(EventArgs &args)
{
    args.x++;
}

struct EventHandlerStruct
{
    void operator()(EventArgs &args)
    {
        args.y++;
    }
};

class EventHandlerClass
{
  public:
    void HandleThatEvent(EventArgs &args)
    {
        args.z++;
    }
};
} // namespace

int test::eventTest::GeneralizedEventTest()
{
    EventHandlerClass c;
    EventHandlerStruct s;
    util::Event<EventArgs> event;
    EventArgs args;

    args.x = 0;
    args.y = 0;
    args.z = 0;

    assert::AreEqual((size_t)0, event.Size());

    {
        event.Register(&StaticEventFunction);

        assert::AreEqual((size_t)1, event.Size());

        event(args);

        assert::AreEqual(1, args.x);
        assert::AreEqual(0, args.y);
        assert::AreEqual(0, args.z);
    }

    {
        event.Register(s);

        assert::AreEqual((size_t)2, event.Size());

        event(args);

        assert::AreEqual(2, args.x);
        assert::AreEqual(1, args.y);
        assert::AreEqual(0, args.z);
    }

    {
        event.Register(&c, &EventHandlerClass::HandleThatEvent);

        assert::AreEqual((size_t)3, event.Size());

        event(args);

        assert::AreEqual(3, args.x);
        assert::AreEqual(2, args.y);
        assert::AreEqual(1, args.z);
    }

    {
        event.Remove(&StaticEventFunction);

        assert::AreEqual((size_t)2, event.Size());

        event(args);

        assert::AreEqual(3, args.x);
        assert::AreEqual(3, args.y);
        assert::AreEqual(2, args.z);
    }

    {
        event.Remove(s);

        assert::AreEqual((size_t)1, event.Size());

        event(args);

        assert::AreEqual(3, args.x);
        assert::AreEqual(3, args.y);
        assert::AreEqual(3, args.z);
    }

    {
        event.Remove(&c, &EventHandlerClass::HandleThatEvent);

        assert::AreEqual((size_t)0, event.Size());

        event(args);

        assert::AreEqual(3, args.x);
        assert::AreEqual(3, args.y);
        assert::AreEqual(3, args.z);
    }

    return 0;
}