#include "event.hpp"
#include "test.hpp"

#define RES_X 10
#define RES_Y 100
#define RES_Z 1000

struct event_args
{
    int x, y, z;
};

struct event_listener : public util::i_event_listener<event_args>
{
    int id;

    event_listener(int id) : id(id)
    {
    }

    void handle_event(event_args &args)
    {
        args.x = RES_X + this->id;
        args.y = RES_Y + this->id;
        args.z = RES_Z + this->id;
    }
};

int test::event_test::test_listener_events()
{
    util::listener_event<event_args> event;
    event_args args = {0, 0, 0};
    event_listener *listener = new event_listener(1);

    assert::are_equal(0u, event.size());

    event += listener;
    assert::are_equal(1u, event.size());

    event(args);

    assert::are_equal(RES_X + listener->id, args.x);
    assert::are_equal(RES_Y + listener->id, args.y);
    assert::are_equal(RES_Z + listener->id, args.z);
    assert::are_equal(1u, event.size());

    event -= listener;
    args = {0, 0, 0};
    event(args);

    assert::are_equal(0, args.x);
    assert::are_equal(0, args.y);
    assert::are_equal(0, args.z);
    assert::are_equal(0u, event.size());

    event(args);

    return 0;
}