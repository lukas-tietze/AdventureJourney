#pragma once

namespace logic
{
class IHandleRound
{
  public:
    virtual void BeforeRoundEnd() = 0;
    virtual void HandleRoundEnd() = 0;
    virtual void BeforeNextRound() = 0;
    virtual void HandleNextRound() = 0;
};
} // namespace logic
