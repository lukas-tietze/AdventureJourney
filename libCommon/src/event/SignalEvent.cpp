#include <csignal>

#include "Event.hpp"
#include "Exception.hpp"

namespace
{
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

    util::StdSignalEvent(args);
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
    if (static_cast<int>(s) & static_cast<int>(util::Signal::Abort))
        std::signal(SIGABRT, &HandleSignal);
    if (static_cast<int>(s) & static_cast<int>(util::Signal::FloatingPointException))
        std::signal(SIGFPE, &HandleSignal);
    if (static_cast<int>(s) & static_cast<int>(util::Signal::IllegalInstruction))
        std::signal(SIGILL, &HandleSignal);
    if (static_cast<int>(s) & static_cast<int>(util::Signal::Interrupt))
        std::signal(SIGINT, &HandleSignal);
    if (static_cast<int>(s) & static_cast<int>(util::Signal::SegmentationViolation))
        std::signal(SIGSEGV, &HandleSignal);
    if (static_cast<int>(s) & static_cast<int>(util::Signal::Terminate))
        std::signal(SIGTERM, &HandleSignal);
}

util::Event<util::SignalEventArgs> util::StdSignalEvent = util::Event<util::SignalEventArgs>();

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