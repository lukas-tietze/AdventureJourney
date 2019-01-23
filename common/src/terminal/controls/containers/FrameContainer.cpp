#include "terminal/controls/containers/FrameContainer.hpp"
#include "Exception.hpp"

terminal::FrameContainer::FrameContainer() : ContainerBase(),
                                             top(nullptr),
                                             bottom(nullptr),
                                             left(nullptr),
                                             right(nullptr),
                                             center(nullptr)
{
}

void terminal::FrameContainer::Add(ControlBase *item)
{
    this->Add(Orientation::Center, item);
}

void terminal::FrameContainer::Add(Orientation where, ControlBase *item)
{
    switch (where)
    {
    case terminal::FrameContainer::Orientation::Left:
        this->left = item;
    case terminal::FrameContainer::Orientation::Right:
        this->right = item;
    case terminal::FrameContainer::Orientation::Top:
        this->top = item;
    case terminal::FrameContainer::Orientation::Bottom:
        this->bottom = item;
    case terminal::FrameContainer::Orientation::Center:
        this->center = item;
    default:
        throw util::InvalidCaseException();
    }

    this->Invalidate();
    this->terminal::ContainerBase::Add(item);
}

void terminal::FrameContainer::RestoreLayout()
{
}
