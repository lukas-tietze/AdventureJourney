#include <ctime>

#include "datetime/timer.hpp"

util::round_timer::round_timer() : m_start((clock_t)-1),
                             m_rounds()
{
}

util::round_timer::round_timer(const round_timer &copy) : m_start(copy.m_start),
                                                    m_rounds(copy.m_rounds)
{
}

void util::round_timer::start()
{
    m_start = clock();
    m_rounds.clear();
}

void util::round_timer::round()
{
    m_rounds.push_back(clock());
}

clock_t util::round_timer::elapsed() const
{
    if (m_rounds.empty())
    {
        return 0;
    }

    return m_rounds.back() - m_start;
}

clock_t util::round_timer::average() const
{
    if (m_rounds.empty())
    {
        return 0;
    }

    clock_t total = m_rounds[0] - m_start;

    for (size_t i = 1; i < m_rounds.size(); i++)
    {
        total += m_rounds[i] - m_rounds[i - 1];
    }

    return total / m_rounds.size();
}

size_t util::round_timer::round_count() const
{
    return m_rounds.size();
}

clock_t util::round_timer::elapsed(size_t round) const
{
    if (round == 0)
    {
        return m_rounds[0] - m_start;
    }

    return m_rounds[round] - m_rounds[round - 1];
}