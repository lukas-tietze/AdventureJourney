#pragma once

#include <csignal>
#include <iostream>

#include "event/FunctionEvent.hpp"

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
};

typedef FunctionEvent<SignalEventArgs> SignalEvent;

void EnableSignalHandling();

void EnableSignalHandling(Signal);

SignalEvent &StdSignalEvent();
} // namespace util