#include <csignal>

#include "event.hpp"
namespace
{
void handle_signal(int what)
{
    util::signal_event_args args;
    args.code = what;

    switch (what)
    {
    case SIGABRT:
        args.signal = util::signal::Abort;
        break;
    case SIGFPE:
        args.signal = util::signal::FloatingPointException;
        break;
    case SIGILL:
        args.signal = util::signal::IllegalInstruction;
        break;
    case SIGINT:
        args.signal = util::signal::Interrupt;
        break;
    case SIGSEGV:
        args.signal = util::signal::SegmentationViolation;
        break;
    case SIGTERM:
        args.signal = util::signal::Terminate;
        break;
    default:
        args.signal = util::signal::Unknown;
        break;
    }
}

// TODO: Fixen
// util::on_signal(args);
} // namespace

util::signal_event::signal_event()
{
    std::signal(SIGABRT, &handle_signal);
    std::signal(SIGFPE, &handle_signal);
    std::signal(SIGILL, &handle_signal);
    std::signal(SIGINT, &handle_signal);
    std::signal(SIGSEGV, &handle_signal);
    std::signal(SIGTERM, &handle_signal);
}