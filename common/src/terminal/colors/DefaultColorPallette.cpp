#include <vector>

#include "terminal/TerminalView.hpp"

terminal::colorPairId_t terminal::controlStyles::controlText = 0;
terminal::colorPairId_t terminal::controlStyles::disabledControlText = 0;
terminal::colorPairId_t terminal::controlStyles::controlBorder = 0;
terminal::colorPairId_t terminal::controlStyles::inactiveControlBorder = 0;
terminal::colorPairId_t terminal::controlStyles::disabledControlBorder = 0;

std::tuple<size_t, size_t> terminal::controlStyles::LoadStyles()
{
    auto &v = *TerminalView::GetInstance();
    ColorPallette *res;

    for (const auto &item : std::vector<terminal::controlStyles::ControlStyleColorPallette *>{
             &terminal::controlStyles::defaultMinimal,
             &terminal::controlStyles::defaultReduced,
             &terminal::controlStyles::defaultFull,
         })
    {
        if (item->GetColorCount() <= v.GetMaxColors() && item->GetColorPairCount() <= v.GetMaxColorPairs())
        {
            v.ApplyColorPallette(*item);

            terminal::controlStyles::controlText = item->GetControlText();
            terminal::controlStyles::disabledControlText = item->GetDisabledControlText();
            terminal::controlStyles::controlBorder = item->GetControlBorder();
            terminal::controlStyles::inactiveControlBorder = item->GetInactiveControlBorder();
            terminal::controlStyles::disabledControlBorder = item->GetDisabledControlBorder();

            return std::make_tuple(item->GetColorCount(), item->GetColorPairCount());
        }
    }

    return std::make_tuple(0, 0);
}