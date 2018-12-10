#pragma once

#include "data/json.hpp"
#include "resources.hpp"
#include "util/id_generator_base.hpp"

namespace logic
{
enum class unit_type
{
    Infantry,
    Armour,
    AirCraft,
    Ship,
};

class unit
{
  private:
    unit_class *type;

    long remaining_hit_points;
};

class space_ship : public unit, public has_name_base
{
  private:
    uint crew;
    uint soldiers;
    uint gunners;
    uint mechanics;
    uint staff;
};

class attachement_type
{

};

class attachement
{

};

class unit_class : public has_name_base, public id_generator_base<unit>, public json::i_json_serializable
{
  private:
    long hit_points;
    long energy_defense;
    long energy_penetration;
    long energy_damage;
    long physical_defense;
    long physical_penetration;
    long physical_damage;
    long movement;

    logic::resource_set upkeep;
};
} // namespace logic