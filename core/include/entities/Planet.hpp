#pragma once

#include <ostream>

#include "Defs.hpp"
#include "entities/Resources.hpp"
#include "util/IdGeneratorBase.hpp"
#include "util/HasNameBase.hpp"
#include "util/HasEngineBase.hpp"
#include "data/Json.hpp"

namespace logic
{
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

std::ostream &operator<<(std::ostream &, const PlanetaryBodyType &);

enum class PopulationEffect
{
    Plague,
    Starvation,
    Mad,
    Unrest,
    Rebellion,
    Resilient,
    Tough,
    Intelligent,
    Industrial,
    Warlike,
    Sad,
    Happy,
    Fanatical,
};

std::ostream &operator<<(std::ostream &, const PopulationEffect &);

class PlanetaryBody : public HasNameBase, public json::IJsonSerializable, public IdGeneratorBase<PlanetaryBody>
{
  private:
    ResourceSet resources;

    PlanetaryBodyType type;
    PopulationEffect effects;

    ulong populationCount;
    double workerPercentage;
    double recruitablePercentage;
    double populationGrowthRate;
    double loyalty;

    double socialGrowthRate;
    double scienceGrowthRate;
    double industryGrowthRate;
    double militaryGrowthRate;
    double projectGrowthRate;
    long developmentLevel;
    long socialLevel;
    long scienceLevel;
    long industryLevel;
    long militaryLevel;
    long projectLevel;

  public:
    PlanetaryBody();

    PlanetaryBodyType GetType() const;

    ulong GetPopulationCount() const;
    ulong GetWorkerCount() const;
    ulong GetWorkerPercentage() const;
    ulong GetRecruitableCount() const;
    ulong GetRecruitablePercentage() const;
    ulong GetPredictedPopulationCount() const;
    ulong GetPopulationGrowthRate() const;
    double GetLoyality() const;
    double GetPredictedLoyality() const;
    PopulationEffect GetPopulationEffects() const;

    long GetSocialLevel() const;
    long GetScienceLevel() const;
    long GetIndustryLevel() const;
    long GetMilitaryLevel() const;
    long GetProjectLevel() const;
    long GetTotalGrowth() const;

    double GetSocialhGrowthRate() const;
    double GetScienceGrowthRate() const;
    double GetIndustryGrowthRate() const;
    double GetMilitaryGrowthRate() const;
    double GetProjectGrowthRate() const;

    long GetSocialGrowth() const;
    long GetScienceGrowth() const;
    long GetIndustryGrowth() const;
    long GetMilitaryGrowth() const;
    long GetProjectGrowth() const;

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};

class PlanetarySystem : public HasEngineBase, public HasNameBase, public json::IJsonSerializable, public IdGeneratorBase<PlanetarySystem>
{
  private:
    std::vector<PlanetaryBody *> planets;

  public:
    PlanetarySystem();

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};
} // namespace logic