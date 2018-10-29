#pragma once

#include <csignal>
#include <iostream>

#include "event/function_event.hpp"

namespace util
{
enum class signal
{
    Abort = SIGABRT,
    FloatingPointException = SIGFPE,
    IllegalInstruction = SIGILL,
    Interrupt = SIGINT,
    SegmentationViolation = SIGSEGV,
    Terminate = SIGTERM,
    Unknown = 0,
};

std::ostream &operator<<(std::ostream &, signal);

struct signal_event_args
{
    util::signal signal;
    int code;
};

typedef function_event<signal_event_args> signal_event;

void enable_signal_handling();

void enable_signal_handling(signal);

signal_event &get_std_signal_event();
} // namespace util