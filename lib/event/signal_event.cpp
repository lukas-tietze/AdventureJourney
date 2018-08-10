#include <csignal>

#include "event.hpp"

void handle_signal(int what)
{
    util::signal_event_args args;
    args.code = what;

    switch (what)
    {
    case SIGABRT:
        args.signal = util::signal::SigAbrt;
        break;
    case SIGFPE:
        args.signal = util::signal::SigFpe;
        break;
    case SIGILL:
        args.signal = util::signal::SigIll;
        break;
    case SIGINT:
        args.signal = util::signal::SigInt;
        break;
    case SIGSEGV:
        args.signal = util::signal::SigSegv;
        break;
    case SIGTERM:
        args.signal = util::signal::SigTerm;
        break;
    default:
        args.signal = util::signal::Unknown;
        break;
    }

    // TODO: Fixen
    // util::on_signal(args);
}

util::signal_event::signal_event()
{
    std::signal(SIGABRT, &handle_signal);
    std::signal(SIGFPE, &handle_signal);
    std::signal(SIGILL, &handle_signal);
    std::signal(SIGINT, &handle_signal);
    std::signal(SIGSEGV, &handle_signal);
    std::signal(SIGTERM, &handle_signal);
}