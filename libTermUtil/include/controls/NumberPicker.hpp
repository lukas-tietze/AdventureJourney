#pragma once

#include "terminal/controls/ControlBase.hpp"
#include "terminal/DataBinderBase.hpp"

namespace terminal
{
class NumberPicker : public ControlBase, public DataBinderBase<uint32_t>
{
  private:
    u_int32_t min;
    u_int32_t max;
    u_int32_t step;
    u_int32_t largeStep;
    bool largeStepEnabled;
    u_int32_t value;

    std::string buf;

  protected:
    uint32_t &GetSelectedValue();
    void HandleValueChanged();

  public:
    NumberPicker();
    ~NumberPicker();

    void SetMin(uint32_t);
    uint32_t GetMin() const;
    void SetMax(uint32_t);
    uint32_t GetMax() const;
    void SetStep(uint32_t);
    uint32_t GetStep() const;
    void SetLargeStep(uint32_t);
    uint32_t GetLargeStep() const;
    void SetValue(uint32_t);
    uint32_t GetValue() const;
    void SetLargeStepEnabled(bool);
    bool IsLargeStepEnabled() const;

    void HandleKey(terminal::KeyInput &);
    void Render(Canvas &);
};
} // namespace terminal
