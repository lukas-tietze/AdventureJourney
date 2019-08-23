#include "data/Random.hpp"

util::Random::Random() : RandomProvider<std::uniform_real_distribution<double>, std::default_random_engine>(std::uniform_real_distribution<double>(0, 1),
                                                                                                             std::default_random_engine(std::random_device()()))
{
}

util::Random::Random(const Random &copy) : RandomProvider<std::uniform_real_distribution<double>, std::default_random_engine>(copy)
{
}

util::Random::Random(Random::result_t seed) : RandomProvider<std::uniform_real_distribution<double>, std::default_random_engine>(std::uniform_real_distribution<double>(0, 1),
                                                                                                                                  std::default_random_engine(seed))
{
}