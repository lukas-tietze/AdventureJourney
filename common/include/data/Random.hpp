#pragma once
//------------------------------------------------------------------------------------------------------------
// Header für verschiedene Zufallsgeneratoren.
//------------------------------------------------------------------------------------------------------------

#include <random>

namespace util
{
// Stellt alle Zufallsgeneratoren dar, die in der Standardbibliothek definiert sind.
enum class RandomEngineType
{
    DefaultRandomEngine,
    MinstdRand,
    MinstdRand0,
    Mt19937,
    Mt19937_64,
    Ranlux23Base,
    Ranlux43Base,
    Ranlux24,
    Ranlux48,
    KnuthB,
    Device,
};

// Eine Verallgemeinerung aller Zufallsgeneratoren.
class CustomEngine
{
  public:
    // Destruktor.
    virtual ~CustomEngine() {}

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
class CustomEngineImp : public CustomEngine
{
  private:
    TEngine engine;

  public:
    uint_fast64_t operator()()
    {
        return this->engine();
    }

    void discard(unsigned long long n)
    {
        this->engine.discard(n);
    }

    void seed(size_t seed)
    {
        this->engine.seed(seed);
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
class CustomEngineImp<std::random_device> : public CustomEngine
{
  private:
    std::random_device engine;

  public:
    uint_fast64_t operator()()
    {
        return this->engine();
    }

    void discard(unsigned long long n)
    {
        //Discard hat hier keinen Nutzen, da die Entropiequelle nicht-deterministisch ist
        //Das verwerfen von Werten kann unter Umständen die Entropiequelle erschöpfen
    }

    void seed(size_t seed)
    {
        //Entropie-quelle kann nicht geseedet werden.
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

template <class TDistribution, class TEngine>
class RandomProvider
{
  private:
    TDistribution distribution;
    TEngine engine;

  public:
    typedef typename TDistribution::result_type result_t;
    typedef typename TEngine::result_type seed_t;

    RandomProvider() : distribution(),
                       engine()

    {
    }

    RandomProvider(seed_t seed) : RandomProvider()
    {
        this->engine.seed(seed);
    }

    RandomProvider(const RandomProvider<TDistribution, TEngine> &copy) : distribution(copy.distribution),
                                                                         engine(copy.engine)
    {
    }

    RandomProvider(const TDistribution &distribution, const TEngine &engine) : distribution(distribution),
                                                                               engine(engine)
    {
    }

    result_t Next();
};

class Random : public RandomProvider<std::uniform_real_distribution<double>, std::default_random_engine>
{
  public:
    Random();
    Random(const Random &copy);
    Random(Random::result_t);

    template <class T = double>
    T Next(T min, T max)
    {
        return static_cast<T>(this->RandomProvider::Next() * (static_cast<Random::result_t>(max) - static_cast<Random::result_t>(min)) + 
                    static_cast<Random::result_t>(min));
    }

    template <class T = double>
    T Next(T max)
    {
        return this->Next(0, max);
    }

    template <class T = double>
    T Next()
    {
        return this->Next(0, std::numeric_limits<T>::max());
    }
};
} // namespace util