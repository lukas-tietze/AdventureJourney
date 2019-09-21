#pragma once

#include <string>

#include "data/Json.hpp"

namespace logic
{
class HasNameBase : public json::IJsonSerializable
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

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};
} // namespace logic