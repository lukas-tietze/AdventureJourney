#pragma once

#include <string>

namespace logic
{
class HasNameBase
{
  private:
    std::string name;

  protected:
    std::string &GetName();
    void SetName(const std::string &);

    HasNameBase(const HasNameBase &);
    HasNameBase(const std::string &);
    HasNameBase();

  public:
    const std::string GetName() const;
};
} // namespace logic