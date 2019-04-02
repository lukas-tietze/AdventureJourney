#pragma once

namespace logic
{
enum class GalaxySize
{
};

enum class GalaxyAge
{
};

enum class GalaxyType
{
};

enum class Difficulty
{
};

enum class CivilisationCount
{
};

enum class PlayerCivilisation
{
};

struct GameConfig
{
    GalaxySize size;
    GalaxyAge age;
    Difficulty difficulty;
    CivilisationCount civilisationCount;

    float resources;
};
} // namespace logic
