#pragma once

#include <string>

namespace logic
{
enum class SpecialProperty
{
};

struct CivilisationConfig
{
  private:
    std::string name;
    std::string history;
    std::string shortDescription;
    std::vector<SpecialProperty> properties;

  public:
};
} // namespace logic
