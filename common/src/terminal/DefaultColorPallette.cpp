#include <vector>

#include "terminal/TerminalView.hpp"

terminal::ColorPallette terminal::controlStyles::default8x16 =
    terminal::ColorPallette(util::Array<util::Color>({
                                util::Color(0, 0, 0, 0),
                            }),
                            util::Array<terminal::ColorPair>({
                                std::make_tuple(0, 0),
                            }));

std::tuple<size_t, size_t> terminal::controlStyles::LoadStyles()
{
    auto &v = *TerminalView::GetInstance();

    for (const auto &item : std::vector<ColorPallette *>{&terminal::controlStyles::default8x16})
    {
        if (item->GetColorCount() <= v.GetMaxColors() && item->GetColorPairCount() <= v.GetMaxColorPairs())
        {
            v.ApplyColorPallette(*item);

            return std::make_tuple(item->GetColorCount(), item->GetColorPairCount());
        }
    }

    return std::make_tuple(0, 0);
}