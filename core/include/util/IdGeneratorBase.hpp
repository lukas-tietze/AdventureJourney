#pragma once

#include "Defs.hpp"
#include "HasIdBase.hpp"

namespace logic
{
template <class T>
class IdGeneratorBase : public HasIdBase
{
  private:
    static id_t next_id;
    static constexpr id_t INVALID_ID = (id_t)-1;

  protected:
    IdGeneratorBase() : HasIdBase(next_id++)
    {
    }

    IdGeneratorBase(const IdGeneratorBase &copy) : HasIdBase(copy.id)
    {
    }

    IdGeneratorBase(IdGeneratorBase &&initializer) : HasIdBase(initializer.id)
    {
        initializer.SetId(INVALID_ID);
    }
};
} // namespace logic
