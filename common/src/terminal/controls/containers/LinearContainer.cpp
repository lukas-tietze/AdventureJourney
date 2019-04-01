#include "terminal/controls/containers/LinearContainer.hpp"
#include "data/Io.hpp"

terminal::LinearContainer::LinearContainer() : orientation(Orientation::TopToBottom)
{
}

terminal::LinearContainer::~LinearContainer()
{
}

void terminal::LinearContainer::Add(ControlBase *item)
{
    this->ContainerBase::Add(item);
}

bool terminal::LinearContainer::Remove(ControlBase *item)
{
    return this->ContainerBase::Remove(item);
}

void terminal::LinearContainer::RestoreLayout()
{
    this->ControlBase::RestoreLayout();

    int totalSize;
    int remainingSize;
    int otherDim;
    int i = 0;

    if (this->orientation == Orientation::TopToBottom || this->orientation == Orientation::BottomToTop)
    {
        remainingSize = this->GetContentBounds().GetHeight();
        otherDim = this->GetContentBounds().GetWidth();
    }
    else
    {
        remainingSize = this->GetContentBounds().GetWidth();
        otherDim = this->GetContentBounds().GetHeight();
    }

    totalSize = remainingSize;

    switch (this->orientation)
    {
    case Orientation::TopToBottom:
        for (auto pos = this->GetControls().begin(), end = this->GetControls().end(); pos != end && remainingSize > 0; ++pos)
        {
            auto control = *pos;
            control->SetLocation(0, totalSize - remainingSize);
            control->ApplyAutoSize(util::Rectangle(0, totalSize - remainingSize, otherDim, remainingSize));
            control->RestoreLayout();
            remainingSize -= control->GetContentBounds().GetHeight();

            util::dbg.WriteLine("Linear Container [%]: fitted [%] to %", this->GetName(), control->GetName(), control->GetContentBounds());
        }

        break;
    case Orientation::BottomToTop:
        for (auto pos = this->GetControls().begin(), end = this->GetControls().end(); pos != end && remainingSize > 0; ++pos)
        {
            auto control = *pos;
            control->SetLocation(0, remainingSize);
            control->ApplyAutoSize(util::Rectangle(0, remainingSize, otherDim, remainingSize));
            control->RestoreLayout();
            remainingSize -= control->GetContentBounds().GetHeight();

            util::dbg.WriteLine("Linear Container [%]: fitted [%] to %", this->GetName(), control->GetName(), control->GetContentBounds());
        }

        break;
    case Orientation::LeftToRight:
        for (auto pos = this->GetControls().begin(), end = this->GetControls().end(); pos != end && remainingSize > 0; ++pos)
        {
            auto control = *pos;
            control->SetLocation(totalSize - remainingSize, 0);
            control->ApplyAutoSize(util::Rectangle(totalSize - remainingSize, 0, remainingSize, otherDim));
            control->RestoreLayout();
            remainingSize -= control->GetContentBounds().GetWidth();

            util::dbg.WriteLine("Linear Container [%]: fitted [%] to %", this->GetName(), control->GetName(), control->GetContentBounds());
        }

        break;
    case Orientation::RightToLeft:
        for (auto pos = this->GetControls().begin(), end = this->GetControls().end(); pos != end && remainingSize > 0; ++pos)
        {
            auto control = *pos;
            control->SetLocation(remainingSize, 0);
            control->ApplyAutoSize(util::Rectangle(remainingSize, 0, remainingSize, otherDim));
            control->RestoreLayout();
            remainingSize -= control->GetContentBounds().GetWidth();

            util::dbg.WriteLine("Linear Container [%]: fitted [%] to %", this->GetName(), control->GetName(), control->GetContentBounds());
        }

        break;
    default:
        throw util::InvalidCaseException::MakeException(this->orientation);
    }
}

void terminal::LinearContainer::SetOrientation(Orientation o)
{
    if (this->orientation != o && (o == Orientation::TopToBottom ||
                                   o == Orientation::BottomToTop ||
                                   o == Orientation::LeftToRight ||
                                   o == Orientation::BottomToTop))
    {
        this->orientation = o;
        this->Invalidate();
    }
}