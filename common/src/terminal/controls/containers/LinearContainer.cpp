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
    int totalSize;
    int remainingSize;
    int otherDim;
    int i = 0;

    if (this->orientation == Orientation::TopToBottom || this->orientation == Orientation::BottomToTop)
    {
        remainingSize = this->GetBounds().GetHeight();
        otherDim = this->GetBounds().GetWidth();
    }
    else
    {
        remainingSize = this->GetBounds().GetWidth();
        otherDim = this->GetBounds().GetHeight();
    }

    totalSize = remainingSize;

    switch (this->orientation)
    {
    case Orientation::TopToBottom:
        for (auto pos = this->GetControls().begin(), end = this->GetControls().end(); pos != end && remainingSize > 0; ++pos)
        {
            auto control = *pos;
            control->SetLocation(0, totalSize - remainingSize);
            control->ApplyAutoSize(util::Dimension(otherDim, remainingSize));
            control->RestoreLayout();
            remainingSize -= control->GetBounds().GetHeight();

            util::dbg.WriteLine("Linear Container [%]: fitted [%] to %", this->GetName(), control->GetName(), control->GetBounds());
        }

        break;
    case Orientation::BottomToTop:
        for (auto pos = this->GetControls().begin(), end = this->GetControls().end(); pos != end && remainingSize > 0; ++pos)
        {
            auto control = *pos;
            control->SetLocation(0, remainingSize);
            control->ApplyAutoSize(util::Dimension(otherDim, remainingSize));
            control->RestoreLayout();
            remainingSize -= control->GetBounds().GetHeight();

            util::dbg.WriteLine("Linear Container [%]: fitted [%] to %", this->GetName(), control->GetName(), control->GetBounds());
        }

        break;
    case Orientation::LeftToRight:
        for (auto pos = this->GetControls().begin(), end = this->GetControls().end(); pos != end && remainingSize > 0; ++pos)
        {
            auto control = *pos;
            control->SetLocation(totalSize - remainingSize, 0);
            control->ApplyAutoSize(util::Dimension(remainingSize, otherDim));
            control->RestoreLayout();
            remainingSize -= control->GetBounds().GetWidth();

            util::dbg.WriteLine("Linear Container [%]: fitted [%] to %", this->GetName(), control->GetName(), control->GetBounds());
        }

        break;
    case Orientation::RightToLeft:
        for (auto pos = this->GetControls().begin(), end = this->GetControls().end(); pos != end && remainingSize > 0; ++pos)
        {
            auto control = *pos;
            control->SetLocation(remainingSize, 0);
            control->ApplyAutoSize(util::Dimension(remainingSize, otherDim));
            control->RestoreLayout();
            remainingSize -= control->GetBounds().GetWidth();

            util::dbg.WriteLine("Linear Container [%]: fitted [%] to %", this->GetName(), control->GetName(), control->GetBounds());
        }

        break;
    default:
        throw util::InvalidCaseException::MakeException(this->orientation);
    }

    this->ControlBase::RestoreLayout();
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