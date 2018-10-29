#pragma once

#include "defs.hpp"
#include "has_id_base.hpp"

namespace logic
{
template <class T>
class id_generator_base : public has_id_base
{
  private:
    static id_t next_id;
    static constexpr id_t INVALID_ID = (id_t)-1;

  protected:
    id_generator_base() : has_id_base(next_id++)
    {
    }

    id_generator_base(const id_generator_base &copy) : has_id_base(copy.id)
    {
    }

    id_generator_base(id_generator_base &&initializer) : has_id_base(initializer.id)
    {
        initializer.set_id(INVALID_ID);
    }
};
} // namespace logic
