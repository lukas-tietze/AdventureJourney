#include "event.hpp"
#include "test.hpp"

#define RES_X 10
#define RES_Y 100
#define RES_Z 1000

struct event_args
{
    int x, y, z;
};

void event_function(event_args &args)
{
    args.x = RES_X;
    args.y = RES_Y;
    args.z = RES_Z;
}

int test::event_test::test_function_events()
{
    util::function_event<event_args> event;
    event_args args = {0, 0, 0};

    assert::are_equal(0u, event.size());
    event += &event_function;
    assert::are_equal(1u, event.size());

    event(args);

    assert::are_equal(RES_X, args.x);
    assert::are_equal(RES_Y, args.y);
    assert::are_equal(RES_Z, args.z);

    assert::are_equal(1u, event.size());
    event -= &event_function;
    assert::are_equal(0u, event.size());

    args = {0, 0, 0};
    event(args);

    assert::are_equal(0, args.x);
    assert::are_equal(0, args.y);
    assert::are_equal(0, args.z);
    assert::are_equal(0u, event.size());

    return 0;
}