#pragma once

#include <string>
#include <vector>
#include <tuple>

#include "util/HasNameBase.hpp"

namespace logic
{
class General;
class Admiral;

class Army : public HasNameBase
{
  private:
    General *leader;
    std::vector<std::tuple<id_t, uint>> units;

  public:
    Army();
};

class Fleet : public HasNameBase
{
  private:
    Admiral *leader;
    std::vector<std::tuple<id_t, uint>> units;
    std::vector<Army *> attachedArmies;

  public:
    Fleet();

};
} // namespace logic