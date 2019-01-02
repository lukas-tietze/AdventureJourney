#pragma once

#include "Defs.hpp"
#include "data/Json.hpp"

namespace logic
{
class HasIdBase : public json::IJsonSerializable
{
  private:
    id_t id;

  protected:
    HasIdBase(id_t);
    HasIdBase(const HasIdBase &);
    HasIdBase();

    void SetId(id_t);

  public:
    id_t GetId() const;

    virtual json::Node *Serialize();
    virtual void Deserialize(const json::Node *);
};
} // namespace logic