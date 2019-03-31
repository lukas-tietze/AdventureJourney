#pragma once

#include <vector>

#include "terminal/controls/ControlBase.hpp"
#include "Event.hpp"

namespace terminal
{
struct OptionSelectedEventArgs
{
    std::string name;
    int marker;
    size_t id;
    bool handled;
};

class Selector : public ControlBase
{
  private:
    struct Item
    {
        std::string text;
        int marker;
    };

    std::vector<Item> selectableItems;
    std::vector<size_t> items;
    size_t selectedItem;
    util::Event<OptionSelectedEventArgs> onOptionSelected;

    char marker;
    bool centerText;
    char seperatorChar;

    colorPairId_t markerStyle;
    colorPairId_t seperatorStyle;
    colorPairId_t selectedOptionForeground;
    colorPairId_t selectedOptionBackground;

  public:
    Selector();

    void AddOption(const std::string &, int marker = 0);
    void AddSeperator(char placeholder = '-');
    bool RemoveOption(const std::string &);
    bool RemoveOption(int);
    bool ClearOptions();

    const std::string &GetSelectedText() const;
    size_t GetSelectedIndex() const;
    int GetSelectedMarker() const;

    virtual void UpdateColors();

    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);
    virtual void Render(Canvas &);

    char GetSeperatorChar() const;
    void SetSeperatorChar(char);
    colorPairId_t GetMarkerStyle() const;
    void SetMarkerStyle(colorPairId_t);
    colorPairId_t GetSeperatorStyle() const;
    void SetSeperatorStyle(colorPairId_t);
    colorPairId_t GetSelectedOptionForeground() const;
    void SetSelectedOptionForeground(colorPairId_t);
    colorPairId_t GetSelectedOptionBackground() const;
    void SetSelectedOptionBackground(colorPairId_t);

    void SetCenterText(bool);
    bool IsTextCentered() const;
    void SetMarker(char);
    void ResetMarker();
    void DisableMarker();
    char GetMarker() const;

    util::Event<OptionSelectedEventArgs> const &OnOptionSelected();
};
} // namespace terminal
