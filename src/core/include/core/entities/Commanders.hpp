#pragma once

#include <string>
#include <vector>

#include "data/Json.hpp"
#include "Defs.hpp"
#include "util/HasNameBase.hpp"
#include "entities/Army.hpp"

namespace logic
{
class CommanderBase : public HasNameBase, public json::IJsonSerializable
{
  private:
    std::vector<std::string> titles;

    int reputation;
    int rank;

  public:
    CommanderBase();

    const std::vector<std::string> &GetTitles() const;
    int GetReputation() const;
    int GetRank() const;
    int GetCommandPoints() const;

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};

class Admiral : public CommanderBase
{
  public:
    Admiral();

    bool can_command(const Fleet &) const;
};

class General : public CommanderBase
{
  public:
    General();

    bool CanCommand(const Army &) const;
};
} // namespace logic