#include "Terminal.hpp"
#include "data/Io.hpp"

terminal::ControlBase::ControlBase() : bounds(0, 0, 0, 0),
                                       contentBounds(0, 0, 0, 0),
                                       paddings({0, 0, 0, 0}),
                                       paddingModes({true, true, true, true}),
                                       parent(nullptr),
                                       zIndex(0),
                                       hasFocus(false),
                                       visible(true),
                                       minimumSize(0, 0),
                                       maximumSize(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()),
                                       autoSizeMode(AutoSizeMode::None),
                                       borderEnabled(false)
{
    // this->name = util::Format("% [%]", typeid(*this).name(), this);
    this->name = util::Format("%", this);
    this->UpdateColors();
}

terminal::ControlBase::~ControlBase()
{
}