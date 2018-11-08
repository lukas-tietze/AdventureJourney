#pragma once

#include "defs.hpp"

namespace logic
{
template <class T>
class entity_id_base
{
  private:
    static id_t next_id;
    static constexpr id_t INVALID_ID = (id_t)-1;
    id_t id;

  protected:
    entity_id_base() : id(next_id++)
    {
    }

    entity_id_base(const entity_id_base &copy) : if (copy.id)
    {
    }

    entity_id_base(entity_id_base &&initializer) : id(initializer.id)
    {
        initializer.id = INVALID_ID;
    }

  public:
    id_t get_id() const
    {
        return this->id;
    }
};
} // namespace logic