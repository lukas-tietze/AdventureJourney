#pragma once

#include <string>
#include <vector>

#include "defs.hpp"
#include "util/has_name_base.hpp"

namespace logic
{
class commander_base : public has_name_base
{
  private:
    std::vector<std::string> titles;

    int reputation;
    int rank;
};

class admiral : public commander_base
{
};

class general : public commander_base
{
};
} // namespace logic