#include <csignal>

#include "Event.hpp"
#include "Exception.hpp"

namespace
{
util::SignalEvent stdSignalEvent;

void HandleSignal(int what)
{
    util::SignalEventArgs args;
    args.code = what;

    switch (what)
    {
    case SIGABRT:
        args.signal = util::Signal::Abort;
        break;
    case SIGFPE:
        args.signal = util::Signal::FloatingPointException;
        break;
    case SIGILL:
        args.signal = util::Signal::IllegalInstruction;
        break;
    case SIGINT:
        args.signal = util::Signal::Interrupt;
        break;
    case SIGSEGV:
        args.signal = util::Signal::SegmentationViolation;
        break;
    case SIGTERM:
        args.signal = util::Signal::Terminate;
        break;
    default:
        args.signal = util::Signal::Unknown;
        break;
    }

    stdSignalEvent(args);
}
} // namespace

void util::EnableSignalHandling()
{
    util::EnableSignalHandling(util::Signal::Abort);
    util::EnableSignalHandling(util::Signal::FloatingPointException);
    util::EnableSignalHandling(util::Signal::IllegalInstruction);
    util::EnableSignalHandling(util::Signal::Interrupt);
    util::EnableSignalHandling(util::Signal::SegmentationViolation);
    util::EnableSignalHandling(util::Signal::Terminate);
}

void util::EnableSignalHandling(Signal s)
{
    switch (s)
    {
    case util::Signal::Abort:
        std::signal(SIGABRT, &HandleSignal);
        break;
    case util::Signal::FloatingPointException:
        std::signal(SIGFPE, &HandleSignal);
        break;
    case util::Signal::IllegalInstruction:
        std::signal(SIGILL, &HandleSignal);
        break;
    case util::Signal::Interrupt:
        std::signal(SIGINT, &HandleSignal);
        break;
    case util::Signal::SegmentationViolation:
        std::signal(SIGSEGV, &HandleSignal);
        break;
    case util::Signal::Terminate:
        std::signal(SIGTERM, &HandleSignal);
        break;
    case util::Signal::Unknown:
    default:
        throw util::InvalidCaseException();
        break;
    }
}

util::SignalEvent &util::StdSignalEvent()
{
    return stdSignalEvent;
}

std::ostream &util::operator<<(std::ostream &s, util::Signal sig)
{
    switch (sig)
    {
    case util::Signal::Abort:
        s << "Abort";
        break;
    case util::Signal::FloatingPointException:
        s << "FloatingPointException";
        break;
    case util::Signal::IllegalInstruction:
        s << "IllegalInstruction";
        break;
    case util::Signal::Interrupt:
        s << "Interrupt";
        break;
    case util::Signal::SegmentationViolation:
        s << "SegmentationViolation";
        break;
    case util::Signal::Terminate:
        s << "Terminate";
        break;
    case util::Signal::Unknown:
        s << "Unknown";
        break;
    }

    return s;
}