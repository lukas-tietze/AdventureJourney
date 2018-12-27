#pragma once

#include <vector>

#include "entities/Planet.hpp"
#include "entities/Resources.hpp"
#include "entities/Planet.hpp"
#include "entities/Army.hpp"

namespace logic
{
class Engine
{
  public:
    Engine();
    ~Engine();

  private:
    std::vector<logic::PlanetarySystem*> planetarySystems;
    std::vector<logic::Resource*> resources;
    std::vector<logic::Army*> armies;
    std::vector<logic::Fleet*> fleets;
};
} // namespace logic
