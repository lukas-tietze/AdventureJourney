#pragma once

namespace logic
{
enum class invasion_strategy
{
    Wait,
    Bombardement,
    DropAssault,
    EstablishBridgeHead
};

enum class space_battle_strategy
{
    Retreat,
    OffensiveRetreat,
    Offensive,
    Defensive,
    Suicidal,
};

enum class land_battle_strategy
{
    Retreat,
    LineBattle,
    Skirmish,
    Assault,
};

class simulation_parameters
{
  private:
};

class simulation_core
{
  private:
  public:
    void run();
};
} // namespace logic