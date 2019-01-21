#pragma once

#include <ostream>

#include "data/Json.hpp"
#include "Resources.hpp"
#include "util/IdGeneratorBase.hpp"
#include "util/HasNameBase.hpp"

namespace logic
{
class Attachement : public HasNameBase, public HasIdBase, public json::IJsonSerializable
{
  private:
    id_t jointId;
    id_t targetId;

    ResourceSet buildCosts;
    ResourceSet upKeep;

    long hitPointsChange;
    long energyDefenseChange;
    long energyPenetrationChange;
    long energyDamageChange;
    long physicalDefenseChange;
    long physicalPenetrationChange;
    long physicalDamageChange;
    long movementChange;

  public:
    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};

std::ostream &operator<<(std::ostream &, const Attachement &);

class UnitClass : public HasNameBase, public HasIdBase, public json::IJsonSerializable
{
  private:
    long hitPoints;
    long energyDefense;
    long energyPenetration;
    long energyDamage;
    long physicalDefense;
    long physicalPenetration;
    long physicalDamage;
    long movement;

    logic::ResourceSet upKeep;

  public:
    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};

std::ostream &operator<<(std::ostream &, const UnitTemplate &);

class UnitTemplate : public HasNameBase, public HasIdBase, public json::IJsonSerializable
{
  public:
    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};

std::ostream &operator<<(std::ostream &, const UnitTemplate &);
} // namespace logic
