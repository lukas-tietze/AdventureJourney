#pragma once

#include "Defs.hpp"
#include "util/IdGeneratorBase.hpp"
#include "util/HasNameBase.hpp"

namespace logic
{
class DevelopmentRate
{
  private:
    long totalValue;
    double growth;
    double science;
    double industry;
    double military;
    double project;

  public:
    long GetTotalValue() const;
    void SetTotalValue(long) const;

    double GetGrowthRate() const;
    double GetScienceRate() const;
    double GetIndustryRate() const;
    double GetMilitaryRate() const;
    double GetProjectRate() const;

    void SetGrowthRate(double) const;
    void SetScienceRate(double) const;
    void SetIndustryRate(double) const;
    void SetMilitaryRate(double) const;
    void SetProjectRate(double) const;

    long GetTotalGrowth() const;
    long GetTotalScience() const;
    long GetTotalIndustry() const;
    long GetTotalMilitary() const;
    long GetTotalProject() const;
};

class Development
{
  private:
    long growth;
    long science;
    long industry;
    long military;
    long project;

  public:
    long GetGrowth() const;
    long GetScience() const;
    long GetIndustry() const;
    long GetMilitary() const;
    long GetProject() const;

    Development operator+(const DevelopmentRate &) const;
    Development operator-(const DevelopmentRate &) const;
    Development &operator+=(const DevelopmentRate &);
    Development &operator-=(const DevelopmentRate &);
};

enum class PlanetaryBodyType
{
    AsteroidBelt,
    Planet,
    Plantoid,
    GasGiant,
    Icy,
    Hot,
    Volcanic,
    Water,
    WellTempered,
};

enum class PopulationEffect
{
    Plague,
    Tough,
    Intelligent,
    Sad,
    Happy,
};

class PopulationState
{
  private:
    ulong total;
    ulong recruitable;
    double growthRate;

  public:
    PopulationState();

    ulong GetTotalCount() const;
    ulong GetWorkerCount() const;
    ulong GetRecruitableCount() const;
    ulong GetPredictedGrowth() const;
};

class PlanetaryBody : public HasNameBase, public IdGeneratorBase<PlanetaryBody>
{
  private:
    DevelopmentRate developmentRate;
    Development totalDevelopment;
    PopulationState population;
    PlanetaryBodyType type;

  public:
    PlanetaryBody();

    const DevelopmentRate &GetDevelopmentRate() const;
    const Development &GetTotalDevelopment() const;
    const PopulationState& GetPopulationState() const;
    PlanetaryBodyType GetType() const;
};

class PlanetarySystem : public HasNameBase, public IdGeneratorBase<PlanetarySystem>
{
  private:
    std::vector<PlanetaryBody *> planets;

  public:
    PlanetarySystem();
};
} // namespace logic