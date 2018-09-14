#pragma once
//------------------------------------------------------------------------------------------------------------
// Header für verschiedene Zufallsgeneratoren.
//------------------------------------------------------------------------------------------------------------

#include <random>

namespace util
{
// Stellt alle Zufallsgeneratoren dar, die in der Standardbibliothek definiert sind.
enum class random_engine_type
{
    DEFAULT_RANDOM_ENGINE,
    MINSTD_RAND,
    MINSTD_RAND0,
    MT19937,
    MT19937_64,
    RANLUX24_BASE,
    RANLUX48_BASE,
    RANLUX24,
    RANLUX48,
    KNUTH_B,
    DEVICE,
};

// Eine Verallgemeinerung aller Zufallsgeneratoren.
class custom_engine
{
  public:
    // Destruktor.
    virtual ~custom_engine() {}

    // Verwirft die nächsten z Zufallszahlen.
    virtual void discard(unsigned long long z) = 0;

    // Liefert die nächste Zufallszahl.
    virtual uint_fast64_t operator()() = 0;

    // Legt einen Startwert für die Erzeugung von Zufallszahlen fest.
    virtual void seed(size_t seed) = 0;

    // Gibt die kleinstmögliche erzeugbare Zahl zurück.
    virtual uint_fast64_t min() = 0;

    // Gibt die größtmögliche erzeugbare Zahl zurück.
    virtual uint_fast64_t max() = 0;
};

// Eine Template-implementierung, die alle Zufallsgeneratoren der Standardengine darstellen kann.
template <class TEngine>
class custom_engine_imp : public custom_engine
{
  private:
    TEngine m_engine;

  public:
    uint_fast64_t operator()()
    {
        return m_engine();
    }

    void discard(unsigned long long n)
    {
        m_engine.discard(n);
    }

    void seed(size_t seed)
    {
        m_engine.seed(seed);
    }

    uint_fast64_t min()
    {
        return TEngine::min();
    }

    uint_fast64_t max()
    {
        return TEngine::max();
    }
};

// Eine Template-Spezialisierung, um die besondere Struktur von random_device abzubilden.
template <>
class custom_engine_imp<std::random_device> : public custom_engine
{
  private:
    std::random_device m_engine;

  public:
    uint_fast64_t operator()()
    {
        return m_engine();
    }

    void discard(unsigned long long n)
    {
    }

    void seed(size_t seed)
    {
    }

    uint_fast64_t min()
    {
        return std::random_device::min();
    }

    uint_fast64_t max()
    {
        return std::random_device::max();
    }
};

// Legt eine Standard-Engine fest, die dann für alle Zufallszahlen genutzt wird.
void set_default_engine(random_engine_type type);

// Legt einen Startwert für die Standardengine fest.
void seed_default_engine(size_t seed);

// Gibt die gesetzte Standardengine zurück.
custom_engine &default_engine();
} // namespace util