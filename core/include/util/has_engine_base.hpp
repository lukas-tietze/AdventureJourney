#pragma once

#include "engine.hpp"

namespace logic
{
class has_engine_base
{
  private:
    engine *e;

  public:
    has_engine_base(engine *);

    const engine *get_engine() const;

  protected:
    engine *get_engine();
};
} // namespace logic
