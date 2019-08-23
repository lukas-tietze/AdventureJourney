#include "datetime/Timer.hpp"

util::Timer::Timer() : start((clock_t)-1),
                 end((clock_t)-1)
{
}

util::Timer::Timer(const Timer &copy) : start(copy.start),
                                  end(copy.end)
{
}

void util::Timer::Start()
{
    this->start = clock();
}

void util::Timer::Stop()
{
    this->end = clock();
}

clock_t util::Timer::Elapsed() const
{
    return this->end - this->start;
}