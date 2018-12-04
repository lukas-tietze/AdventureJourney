#pragma once

namespace logic
{
enum class InvasionStrategy
{
    Wait,
    Bombardement,
    DropAssault,
    EstablishBridgeHead
};

enum class SpaceBattleStrategy
{
    Retreat,
    OffensiveRetreat,
    Offensive,
    Defensive,
    Suicidal,
};

enum class LandBattleStrategy
{
    Retreat,
    LineBattle,
    Skirmish,
    Assault,
};

class SimulationParameters
{
  private:
};

class SimulationCore
{
  private:
  public:
    void Run();
};
} // namespace logic