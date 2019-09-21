#pragma once

#include <string>

#include "data/Json.hpp"
#include "data/collection/Array.hpp"
#include "util/HasNameBase.hpp"
#include "util/HasIdBase.hpp"

namespace logic
{
class Resource : public HasNameBase, public HasIdBase, public json::IJsonSerializable
{
  private:
    int rarity;

  public:
    int GetRarity() const;

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};

class ResourceSet : public json::IJsonSerializable
{
  private:
    util::Array<long> items;

  public:
    ResourceSet();

    long GetAmountOf(id_t) const;
    long GetAmountOf(const Resource &) const;

    void SetAmountOf(id_t, long);
    void SetAmountOf(const Resource &, long);

    bool CanSatisfyRequirements(const ResourceSet &);
    bool CanSatisfyRequirement(id_t, long);
    bool CanSatisfyRequirement(const Resource &, long);

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);

    ResourceSet operator+(const ResourceSet &other) const;
    ResourceSet operator-(const ResourceSet &other) const;
    ResourceSet operator/(const ResourceSet &other) const;
    ResourceSet operator*(const ResourceSet &other) const;
    ResourceSet &operator+=(const ResourceSet &other);
    ResourceSet &operator-=(const ResourceSet &other);
    ResourceSet &operator*=(const ResourceSet &other);
    ResourceSet &operator/=(const ResourceSet &other);
};
} // namespace logic