#include "data/random.hpp"

util::random::random() : random_provider<std::uniform_real_distribution<double>, std::default_random_engine>(std::uniform_real_distribution<double>(0, 1),
                                                                                                             std::default_random_engine(std::random_device()()))
{
}

util::random::random(const random &copy) : random_provider<std::uniform_real_distribution<double>, std::default_random_engine>(copy)
{
}

util::random::random(random::result_t seed) : random_provider<std::uniform_real_distribution<double>, std::default_random_engine>(std::uniform_real_distribution<double>(0, 1),
                                                                                                                                  std::default_random_engine(seed))
{
}