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
    
    std::vector<Item> items;
    size_t selectedItem;
    util::Event<OptionSelectedEventArgs> onOptionSelected;

  public:
    Selector();

    void AddOption(const std::string &, int marker = 0);
    bool RemoveOption(const std::string &);

    const std::string &GetSelectedText() const;
    size_t GetSelectedIndex() const;
    int GetSelectedMarker() const;

    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);
    virtual void Render(Canvas &);

    util::Event<OptionSelectedEventArgs> const &OnOptionSelected();
};
} // namespace terminal
