#include "terminal/controls/containers/FrameContainer.hpp"
#include "Exception.hpp"

terminal::FrameContainer::FrameContainer() : ContainerBase(),
                                             controls(),
                                             weights(),
                                             weightsFixed()
{
}

terminal::FrameContainer::~FrameContainer()
{
}

void terminal::FrameContainer::Add(ControlBase *item)
{
    this->Add(Orientation::Center, item);
}

void terminal::FrameContainer::Add(Orientation where, ControlBase *item)
{
    auto id = -1;

    switch (where)
    {
    case terminal::FrameContainer::Orientation::Left:
    case terminal::FrameContainer::Orientation::Right:
    case terminal::FrameContainer::Orientation::Top:
    case terminal::FrameContainer::Orientation::Bottom:
    case terminal::FrameContainer::Orientation::Center:
        id = static_cast<int>(where);
        break;
    default:
        throw util::InvalidCaseException();
    }

    if (this->controls[id] != nullptr)
    {
        this->terminal::ContainerBase::Remove(this->controls[id]);
    }

    this->controls[id] = item;
    this->terminal::ContainerBase::Add(item);

    this->Invalidate();
}

bool terminal::FrameContainer::Remove(ControlBase *control)
{
    for (int i = 0; i < 5; i++)
    {
        if (this->controls[i] == control)
            this->controls[i] = nullptr;
    }

    this->ContainerBase::Remove(control);
}

void terminal::FrameContainer::RestoreLayout()
{
    auto offset = this->GetLocation();
    auto remainingSpace = util::Rectangle(0, 0, this->GetSize());

    for (auto control : this->controls)
    {
        control->ApplyAutoSize(this->GetSize());
        control->RestoreLayout();
    }
}

void terminal::FrameContainer::Render(Canvas &c)
{
    this->ContainerBase::Render(c);
}
