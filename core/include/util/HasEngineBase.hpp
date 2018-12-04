#pragma once

#include "Engine.hpp"

namespace logic
{
class HasEngineBase
{
  private:
    Engine *e;

  public:
    HasEngineBase(Engine *);

    const Engine *get_engine() const;

  protected:
    Engine *get_engine();
};
} // namespace logic
