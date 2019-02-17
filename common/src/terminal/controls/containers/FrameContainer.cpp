#include <cstring>

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

void terminal::FrameContainer::SetWeight(Orientation where, int value)
{
    auto id = static_cast<int>(where);

    this->weights[id] = value;
    this->weightsFixed[id] = value >= 0;
}

void terminal::FrameContainer::SetMaxSize(Orientation where, int value)
{
    auto id = static_cast<int>(where);

    this->maxSizes[id] = value;
    this->minSizes[id] = util::Min(value - 1, this->minSizes[id]);
}

void terminal::FrameContainer::SetMinSize(Orientation where, int value)
{
    auto id = static_cast<int>(where);

    this->minSizes[id] = value;
    this->maxSizes[id] = util::Max(value + 1, this->maxSizes[id]);
}

void terminal::FrameContainer::Add(ControlBase *item)
{
    for (int i = 0; i < 5; i++)
    {
        if (this->controls[i] == nullptr)
        {
            this->Add(static_cast<terminal::FrameContainer::Orientation>(i), item);
            break;
        }
    }
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
    auto remainingArea = util::Rectangle(0, 0, this->GetSize());

    int order[5] = {0, 1, 2, 3, 4};

    // for (int i = 0; i < 5; i++)
    // {
    //     for (int j = 0; j < 5; j++)
    //     {
    //         if (this->weights[j] < this->weights[order[i]] &&
    //             (i == 0 || this->weights[j] > this->weights[i - 1]))
    //         {
    //             order[i] = j;
    //         }
    //     }
    // }

    int id;
    ControlBase *control;
    int size;

    for (int i = 0; i < 5; i++)
    {
        id = order[i];
        control = this->controls[id];
        size = remainingArea.GetWidth();

        if (this->minSizes[id] > 0)
            size = util::Max(this->minSizes[id], size);

        if (this->maxSizes[id] > 0)
            size = util::Min(this->maxSizes[id], size);

        switch (static_cast<Orientation>(id))
        {
        case Orientation::Left:
            space = remainingArea.GetLeftSub(size);
            remainingArea.MoveLeftEdge(size);
            break;
        case Orientation::Right:
            space = remainingArea.GetRightSub(size);
            remainingArea.MoveRightEdge(-size);
            break;
        case Orientation::Top:
            space = remainingArea.GetTopSub(size);
            remainingArea.MoveTopEdge(size);
            break;
        case Orientation::Bottom:
            space = remainingArea.GetBottomSub(size);
            remainingArea.MoveBottomEdge(-size);
            break;
        case Orientation::Center:
            space = remainingArea;
            auto buf = 0;

            if ((buf = this->minSizes[static_cast<int>(Orientation::Left)]) > 0)
            {
                space.MoveLeftEdge(buf);
            }

            remainingArea = space;
            break;
        default:
            throw util::InvalidCaseException();
        }

        control->ApplyAutoSize(space.GetSize());
        control->SetLocation(space.GetLocation() + this->GetLocation());
        control->RestoreLayout();
    }
}

void terminal::FrameContainer::Render(Canvas &c)
{
    this->ContainerBase::Render(c);
}