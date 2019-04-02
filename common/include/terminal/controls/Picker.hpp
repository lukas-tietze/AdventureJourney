#pragma once

#include <vector>

#include "terminal/controls/ControlBase.hpp"

namespace terminal
{
class Picker : public ControlBase
{
  private:
    struct Option
    {
        std::string value;
        int marker;
        bool hasStyle;
        colorPairId_t style;
    };

    std::vector<Option> options;
    bool circleOptions;
    bool horizontalMode;
    size_t selectedOption;

  public:
    Picker();
    ~Picker();

    void AddOption(const std::string &value, int marker = 0);
    void AddStyledOption(const std::string &value, colorPairId_t style, int marker = 0);
    bool RemoveOption(const std::string &);
    bool RemoveOption(int);
    bool ClearOptions();

    void SetCircleOptions(bool);
    bool IsCircleOptionsSet() const;
    void SetHorizontalMode(bool);
    bool IsHorizontalModeSet() const;

    void HandleKey(KeyInput &);
    void Render(Canvas &);
};
} // namespace terminal