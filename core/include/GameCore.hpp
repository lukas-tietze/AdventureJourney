#pragma once

#include "engine/GameConfig.hpp"
#include "engine/Engine.hpp"
#include "engine/CivilisationConfig.hpp"
#include "engine/Profile.hpp"
#include "engine/Settings.hpp"

namespace logic
{
class GameCore
{
  private:
    Settings settings;
    Engine engine;
    std::vector<CivilisationConfig> civilisations;
    Profile playerProfile;
    GameConfig gameConfig;

  public:
    Settings &GetSettings();
    const Settings &GetSettings() const;

    Profile &GetProfile();
    const Profile &GetProfile() const;

    GameConfig &GetGameConfig();
};
} // namespace logic
