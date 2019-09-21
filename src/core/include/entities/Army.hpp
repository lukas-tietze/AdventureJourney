#pragma once

#include <string>
#include <vector>
#include <tuple>

#include "data/Json.hpp"
#include "util/HasNameBase.hpp"

namespace logic
{
class General;
class Admiral;

class Army : public HasNameBase, public json::IJsonSerializable
{
  private:
    General *leader;
    std::vector<std::tuple<id_t, uint>> units;

  public:
    Army();

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};

class Fleet : public HasNameBase, public json::IJsonSerializable
{
  private:
    Admiral *leader;
    std::vector<std::tuple<id_t, uint>> units;
    std::vector<Army *> attachedArmies;

  public:
    Fleet();

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};
} // namespace logic