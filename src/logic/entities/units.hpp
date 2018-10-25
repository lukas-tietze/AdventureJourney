#pragma once

#include "data/json.hpp"
#include "entity_bases.hpp"

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
    id_t class_id;

    long remaining_hit_points;
};

class carrier_unit : public unit
{
  private:
};

class space_ship
{
  private:
    std::string name;
};

class unit_class : public entity_id_base<unit>, json::i_json_serializable
{
  private:
    std::string name;

    long hit_points;
    long energy_defense;
    long energy_penetration;
    long energy_damage;
    long physical_defense;
    long physical_penetration;
    long physical_damage;
    long movement;
};
} // namespace logic