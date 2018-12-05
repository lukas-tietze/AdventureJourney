#include <ctime>

#include "datetime/Timer.hpp"

util::RoundTimer::RoundTimer() : start((clock_t)-1),
                                 rounds()
{
}

util::RoundTimer::RoundTimer(const RoundTimer &copy) : start(copy.start),
                                                       rounds(copy.rounds)
{
}

void util::RoundTimer::Start()
{
    this->rounds.clear();
    this->start = clock();
}

void util::RoundTimer::Round()
{
    this->rounds.push_back(clock());
}

clock_t util::RoundTimer::Elapsed() const
{
    return this->rounds.empty() ? 0 : rounds.back() - start;
}

clock_t util::RoundTimer::Average() const
{
    if (this->rounds.empty())
    {
        return 0;
    }

    clock_t total = this->rounds[0] - this->start;

    for (size_t i = 1; i < rounds.size(); i++)
    {
        total += rounds[i] - rounds[i - 1];
    }

    return total / rounds.size();
}

size_t util::RoundTimer::RoundCount() const
{
    return this->rounds.size();
}

clock_t util::RoundTimer::Elapsed(size_t round) const
{
    if (round == 0)
    {
        return this->rounds[0] - this->start;
    }

    return this->rounds[round] - this->rounds[round - 1];
}