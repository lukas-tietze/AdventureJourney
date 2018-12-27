#pragma once

#include "data/Json.hpp"
#include "Resources.hpp"
#include "util/IdGeneratorBase.hpp"
#include "util/HasNameBase.hpp"

namespace logic
{
enum class UnitType
{
    Infantry,
    Armour,
    AirCraft,
    Ship,
};

class Unit
{  private:
    UnitTemplate *type;

    long remaining_hit_points;
};

class SpaceShip : public Unit, public HasNameBase
{
  private:
    uint crew;
    uint soldiers;
    uint gunners;
    uint mechanics;
    uint staff;
};

class AttachementType
{

};

class Attachement
{

};

class UnitTemplate : public HasNameBase, public IdGeneratorBase<Unit>, public json::IJsonSerializable
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

    logic::ResourceSet upkeep;
};
} // namespace logic