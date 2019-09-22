#pragma once

#include "Defs.hpp"
#include "HasIdBase.hpp"

namespace logic
{
template <class T>
class IdGeneratorBase : public HasIdBase
{
  private:
    static id_t nextId;
    static constexpr id_t InvalidId = (id_t)-1;

  protected:
    IdGeneratorBase() : HasIdBase(nextId++)
    {
    }

    IdGeneratorBase(const IdGeneratorBase &copy) : HasIdBase(copy.id)
    {
    }

    IdGeneratorBase(IdGeneratorBase &&initializer) : HasIdBase(initializer.id)
    {
        initializer.SetId(InvalidId);
    }
};
} // namespace logic
