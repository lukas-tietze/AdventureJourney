#include "Test.hpp"
#include "libCommon/test/TestList.hpp"
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

struct EventListener : public util::IEventListener<EventArgs>
{
    int id;

    EventListener(int id) : id(id)
    {
    }

    void HandleEvent(EventArgs &args)
    {
        args.x = RES_X + this->id;
        args.y = RES_Y + this->id;
        args.z = RES_Z + this->id;
    }
};
} // namespace

int test::eventTest::ListenerEvents()
{
    util::ListenerEvent<EventArgs> event;
    EventArgs args = {0, 0, 0};
    EventListener *listener = new EventListener(1);

    assert::AreEqual(size_t(0), event.Size());

    event += listener;
    assert::AreEqual(size_t(1), event.Size());

    event(args);

    assert::AreEqual(RES_X + listener->id, args.x);
    assert::AreEqual(RES_Y + listener->id, args.y);
    assert::AreEqual(RES_Z + listener->id, args.z);
    assert::AreEqual(size_t(1), event.Size());

    event -= listener;
    args = {0, 0, 0};
    event(args);

    assert::AreEqual(0, args.x);
    assert::AreEqual(0, args.y);
    assert::AreEqual(0, args.z);
    assert::AreEqual(size_t(0), event.Size());

    event(args);

    return 0;
}