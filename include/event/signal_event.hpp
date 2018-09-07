#pragma once

#include <csignal>

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

struct signal_event_args
{
    util::signal signal;
    int code;
};

class signal_event : public function_event<signal_event_args>
{
  public:
    signal_event();
    ~signal_event();
};
} // namespace util