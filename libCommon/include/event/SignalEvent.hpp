#pragma once

#include <csignal>
#include <iostream>

#include "event/GeneralizedEvent.hpp"

namespace util
{
enum class Signal
{
    Abort = SIGABRT,
    FloatingPointException = SIGFPE,
    IllegalInstruction = SIGILL,
    Interrupt = SIGINT,
    SegmentationViolation = SIGSEGV,
    Terminate = SIGTERM,
    Unknown = 0,
};

std::ostream &operator<<(std::ostream &, Signal);

struct SignalEventArgs
{
    util::Signal signal;
    int code;
    bool handled;
};

void EnableSignalHandling();
void EnableSignalHandling(Signal);

extern Event<SignalEventArgs> StdSignalEvent;
} // namespace util