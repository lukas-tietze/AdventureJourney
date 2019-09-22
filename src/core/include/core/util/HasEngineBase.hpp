#pragma once

namespace logic
{
class Engine;

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
