#pragma once

#include <ostream>

#include "data/Json.hpp"
#include "Resources.hpp"
#include "util/IdGeneratorBase.hpp"
#include "util/HasNameBase.hpp"
#include "Builder.hpp"

namespace logic
{
enum class UnitType
{
    Infantry,
    Armour,
    AirCraft,
    Ship,
};

std::ostream &operator<<(std::ostream &, const UnitType &);

class Unit : public json::IJsonSerializable
{
  private:
    UnitTemplate *type;

    long remaining_hit_points;

  public:
    virtual ~Unit();

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};

std::ostream &operator<<(std::ostream &, const Unit &);

class SpaceShip : public Unit, public HasNameBase
{
  private:
    uint crew;
    uint soldiers;
    uint gunners;
    uint mechanics;
    uint staff;

  public:
    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};

std::ostream &operator<<(std::ostream &, const SpaceShip &);
} // namespace logic