#pragma once

#include "defs.hpp"

namespace logic
{
class has_id_base
{
  private:
    id_t id;

  protected:
    has_id_base(id_t);
    has_id_base(const has_id_base &);
    has_id_base();

    void set_id(id_t);

  public:
    id_t get_id() const;
};
} // namespace logic