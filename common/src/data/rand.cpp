#include <functional>
#include <random>

#include "data/rand.hpp"

namespace
{
util::custom_engine *m_engine = nullptr;
}

void util::seed_default_engine(size_t seed)
{
    if (m_engine != nullptr)
    {
        m_engine->seed(seed);
    }
}

void util::set_default_engine(util::random_engine_type type)
{
    if (m_engine != nullptr)
    {
        delete m_engine;
    }

    switch (type)
    {
    case random_engine_type::DEFAULT_RANDOM_ENGINE:
        m_engine = new custom_engine_imp<std::default_random_engine>();
        break;
    case random_engine_type::MINSTD_RAND:
        m_engine = new custom_engine_imp<std::minstd_rand>();
        break;
    case random_engine_type::MINSTD_RAND0:
        m_engine = new custom_engine_imp<std::minstd_rand0>();
        break;
    case random_engine_type::MT19937:
        m_engine = new custom_engine_imp<std::mt19937>();
        break;
    case random_engine_type::MT19937_64:
        m_engine = new custom_engine_imp<std::mt19937_64>();
        break;
    case random_engine_type::RANLUX24_BASE:
        m_engine = new custom_engine_imp<std::ranlux24_base>();
        break;
    case random_engine_type::RANLUX48_BASE:
        m_engine = new custom_engine_imp<std::ranlux48_base>();
        break;
    case random_engine_type::RANLUX24:
        m_engine = new custom_engine_imp<std::ranlux24>();
        break;
    case random_engine_type::RANLUX48:
        m_engine = new custom_engine_imp<std::ranlux48>();
        break;
    case random_engine_type::KNUTH_B:
        m_engine = new custom_engine_imp<std::knuth_b>();
        break;
    case random_engine_type::DEVICE:
        m_engine = new custom_engine_imp<std::random_device>();
        break;
    }
}

util::custom_engine &default_engine()
{
    return *m_engine;
}