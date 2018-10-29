#include "datetime/timer.hpp"

util::timer::timer() : m_start((clock_t)-1),
                 m_end((clock_t)-1)
{
}

util::timer::timer(const timer &copy) : m_start(copy.m_start),
                                  m_end(copy.m_end)
{
}

void util::timer::start()
{
    m_start = clock();
}

void util::timer::stop()
{
    m_end = clock();
}

clock_t util::timer::elapsed() const
{
    return m_end - m_start;
}