#include <csignal>

#include "event.hpp"
#include "exception.hpp"

namespace
{
util::signal_event std_signal_event;

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

    std_signal_event(args);
}
} // namespace

void util::enable_signal_handling()
{
    util::enable_signal_handling(util::signal::Abort);
    util::enable_signal_handling(util::signal::FloatingPointException);
    util::enable_signal_handling(util::signal::IllegalInstruction);
    util::enable_signal_handling(util::signal::Interrupt);
    util::enable_signal_handling(util::signal::SegmentationViolation);
    util::enable_signal_handling(util::signal::Terminate);
}

void util::enable_signal_handling(signal s)
{
    switch (s)
    {
    case util::signal::Abort:
        std::signal(SIGABRT, &handle_signal);
        break;
    case util::signal::FloatingPointException:
        std::signal(SIGFPE, &handle_signal);
        break;
    case util::signal::IllegalInstruction:
        std::signal(SIGILL, &handle_signal);
        break;
    case util::signal::Interrupt:
        std::signal(SIGINT, &handle_signal);
        break;
    case util::signal::SegmentationViolation:
        std::signal(SIGSEGV, &handle_signal);
        break;
    case util::signal::Terminate:
        std::signal(SIGTERM, &handle_signal);
        break;
    case util::signal::Unknown:
    default:
        throw util::invalid_case_exception();
        break;
    }
}

util::signal_event &util::get_std_signal_event()
{
    return std_signal_event;
}

std::ostream &util::operator<<(std::ostream &s, util::signal sig)
{
    switch (sig)
    {
    case util::signal::Abort:
        s << "Abort";
        break;
    case util::signal::FloatingPointException:
        s << "FloatingPointException";
        break;
    case util::signal::IllegalInstruction:
        s << "IllegalInstruction";
        break;
    case util::signal::Interrupt:
        s << "Interrupt";
        break;
    case util::signal::SegmentationViolation:
        s << "SegmentationViolation";
        break;
    case util::signal::Terminate:
        s << "Terminate";
        break;
    case util::signal::Unknown:
        s << "Unknown";
        break;
    }

    return s;
}