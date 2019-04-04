#pragma once

#include "data/Json.hpp"

namespace logic
{
class Achievement : public json::IJsonSerializable
{
  private:
    int id;
    std::string name;
    std::string targetDescription;
    std::string metaDescription;

  public:
    Achievement();

    const std::string &GetName() const;
    const std::string &GetTargetDescription() const;
    const std::string &GetMetaDescription() const;

    json::Node *Serialize();
    void Deserialize(const json::Node *);
};
} // namespace logic
