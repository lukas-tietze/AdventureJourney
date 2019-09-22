#pragma once

#include "data/Json.hpp"
#include "util/HasIdBase.hpp"
#include "util/HasNameBase.hpp"

namespace logic
{
class Product : public HasNameBase, public HasIdBase, public json::IJsonSerializable
{
  public:
    Product();

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};
} // namespace logic