#pragma once

#include "Defs.hpp"

namespace logic
{
class HasIdBase
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
};
} // namespace logic