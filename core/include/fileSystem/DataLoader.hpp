#pragma once

#include <string>
#include <vector>

namespace logic
{

class Loader
{
  private:
  public:
    Loader();
    Loader(const std::string &);

    const std::string &SavedGamesDir() const;
    const std::string &SettingsFile() const;
    const std::string &AssetsDir() const;
    const std::string &ShaderDir() const;
    const std::string &UnitSpecificationDir() const;
    const std::string &FactionSpecificationDir() const;
    const std::string &DataValidationDir() const;
};
} // namespace logic
