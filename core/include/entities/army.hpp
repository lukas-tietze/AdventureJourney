#pragma once

#include <string>
#include <vector>
#include <tuple>

#include "util/has_name_base.hpp"

namespace logic
{
class general;
class admiral;

class army : public has_name_base
{
  private:
    general *leader;
    std::vector<std::tuple<id_t, uint>> units;

  public:
    army();
};

class fleet : public has_name_base
{
  private:
    admiral *leader;
    std::vector<std::tuple<id_t, uint>> units;

  public:
    fleet();
};
} // namespace logic