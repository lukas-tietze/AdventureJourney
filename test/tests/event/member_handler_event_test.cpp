#include "event.hpp"
#include "test.hpp"

namespace
{
constexpr int RES_X = 10;
constexpr int RES_Y = 100;
constexpr int RES_Z = 1000;
} // namespace

struct event_args
{
    int x, y, z;
};

struct event_handler
{
    int id;

    void handle_some_event(event_args &args)
    {
        args.x = RES_X + id;
        args.y = RES_Y + id;
        args.z = RES_Z + id;
    }
};

int test::event_test::test_member_handler_events()
{
    util::member_event<event_args> event;
    event_handler handler = {1};
    auto member_handler = util::make_member_handler(&handler, &event_handler::handle_some_event);
    event_args args = {0, 0, 0};

    assert::are_equal(0u, event.size());
    event += member_handler;
    assert::are_equal(1u, event.size());

    event(args);

    assert::are_equal(RES_X + handler.id, args.x);
    assert::are_equal(RES_Y + handler.id, args.y);
    assert::are_equal(RES_Z + handler.id, args.z);

    assert::are_equal(1u, event.size());
    event -= member_handler;
    assert::are_equal(0u, event.size());

    args = {0, 0, 0};
    event(args);

    assert::are_equal(0, args.x);
    assert::are_equal(0, args.y);
    assert::are_equal(0, args.z);
    assert::are_equal(0u, event.size());

    return 0;
}