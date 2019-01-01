#pragma once

#include "Defs.hpp"
#include "util/IdGeneratorBase.hpp"
#include "util/HasNameBase.hpp"
#include "util/HasEngineBase.hpp"
#include "data/Json.hpp"

namespace logic
{
class DevelopmentRate : public json::IJsonSerializable
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

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};

class Development : public json::IJsonSerializable
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

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
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

class PopulationState : public json::IJsonSerializable
{
  private:
    ulong total;
    double workerPercentage;
    double recruitablePercentage;
    double growthRate;
    double loyality;
    PopulationEffect effects;

  public:
    PopulationState();

    ulong GetTotalCount() const;
    ulong GetWorkerCount() const;
    ulong GetRecruitableCount() const;
    ulong GetPredictedGrowth() const;
    ulong GetGrowthRate() const;
    double GetLoyality() const;
    double GetPredictedLoyality() const;
    PopulationEffect GetEffects() const;

    DevelopmentRate ModifyDevelopmentRate(const DevelopmentRate &) const;

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};

class PlanetaryBody : public HasNameBase, public json::IJsonSerializable, public IdGeneratorBase<PlanetaryBody>
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
    const PopulationState &GetPopulationState() const;
    PlanetaryBodyType GetType() const;

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