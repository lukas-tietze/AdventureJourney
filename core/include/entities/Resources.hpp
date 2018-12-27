#pragma once

#include <string>

#include "data/collection/Array.hpp"
#include "util/IdGeneratorBase.hpp"

namespace logic
{
class Resource : public HasNameBase, public IdGeneratorBase<Resource>
{
  private:
};

class ResourceSet
{
  private:
    util::Array<long> items;

  public:
    long GetAmountOf(id_t) const;
    long GetAmountOf(const Resource &) const;

    void SetAmountOf(id_t, long);
    void SetAmountOf(const Resource &, long);

    bool CanSatisfyRequirements(const ResourceSet &);
    bool CanSatisfyRequirement(id_t, long);
    bool CanSatisfyRequirement(const Resource &, long);

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