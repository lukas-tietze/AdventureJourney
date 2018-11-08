#pragma once

#include <string>
#include <vector>

#include "defs.hpp"
#include "util/has_name_base.hpp"
#include "entities/army.hpp"

namespace logic
{
class commander_base : public has_name_base
{
  private:
    std::vector<std::string> titles;

    int reputation;
    int rank;

  public:
    commander_base();

    const std::vector<std::string> &get_titles() const;
    int get_reputation() const;
    int get_rank() const;
    int get_command_points() const;
};

class admiral : public commander_base
{
  public:
    admiral();

    bool can_command(const fleet &) const;
};

class general : public commander_base
{
  public:
    general();

    bool can_command(const army &) const;
};
} // namespace logic