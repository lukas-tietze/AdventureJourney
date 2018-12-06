#include "terminal/Canvas.hpp"
#include "data/Helper.hpp"

terminal::Canvas::Canvas(TerminalView *view) : view(view),
                                               size(view->GetSize()),
                                               clippedArea(0, 0, this->size),
                                               origin(0, 0)
{
    this->view->SetLiveMode(false);
}

terminal::Canvas::Canvas(const Canvas &copy) : view(copy.view),
                                               size(copy.size),
                                               clippedArea(copy.clippedArea),
                                               origin(copy.origin)
{
}

terminal::Canvas &terminal::Canvas::DrawVerticalLine(const util::Point &p, int length, char c)
{
    auto start = this->clippedArea.Fit(p);
    auto end = this->clippedArea.Fit(p + util::Point(0, length));

    for (int y = start.GetY(); y < end.GetY(); y++)
    {
        this->view->Print(c, start.GetX(), y);
    }

    return *this;
}

terminal::Canvas &terminal::Canvas::DrawVerticalLine(const util::Point &p, int length, char c, int color)
{
    auto activeColor = this->view->GetActiveColorPair();
    this->view->SetActiveColorPair(color);
    this->DrawVerticalLine(p, length, c);
    this->view->SetActiveColorPair(activeColor);
}

terminal::Canvas &terminal::Canvas::DrawHorizontalLine(const util::Point &p, int length, char c)
{
    auto start = this->clippedArea.Fit(p);
    auto end = this->clippedArea.Fit(p + util::Point(length, 0));

    for (int x = start.GetX(); x < end.GetX(); x++)
    {
        this->view->Print(c, x, start.GetY());
    }

    return *this;
}

terminal::Canvas &terminal::Canvas::DrawHorizontalLine(const util::Point &p, int length, char c, int color)
{
    auto activeColor = this->view->GetActiveColorPair();
    this->view->SetActiveColorPair(color);
    this->DrawHorizontalLine(p, length, c);
    this->view->SetActiveColorPair(activeColor);
}

terminal::Canvas &terminal::Canvas::DrawBox(const util::Rectangle &r, char horizontal, char vertical, char cornor)
{
    auto tlc = this->clippedArea.Fit(util::Point(r.GetMinX(), r.GetMinY()));
    auto brc = this->clippedArea.Fit(util::Point(r.GetMaxX() - 1, r.GetMaxY() - 1));

    for (int x = tlc.GetX() + 1; x < brc.GetX(); x++)
    {
        this->view->Print(horizontal, x, tlc.GetY());
        this->view->Print(horizontal, x, brc.GetY());
    }

    for (int y = tlc.GetY() + 1; y < brc.GetY(); y++)
    {
        this->view->Print(vertical, tlc.GetX(), y);
        this->view->Print(vertical, brc.GetX(), y);
    }

    this->view->Print(cornor, tlc.GetX(), tlc.GetY());
    this->view->Print(cornor, brc.GetX(), tlc.GetY());
    this->view->Print(cornor, tlc.GetX(), brc.GetY());
    this->view->Print(cornor, brc.GetX(), brc.GetY());

    return *this;
}

terminal::Canvas &terminal::Canvas::DrawBox(const util::Rectangle &r, char c, int color)
{
    auto activeColor = this->view->GetActiveColorPair();
    this->view->SetActiveColorPair(color);
    this->DrawBox(r, c);
    this->view->SetActiveColorPair(activeColor);
}

terminal::Canvas &terminal::Canvas::DrawBox(const util::Rectangle &r, char horizontal, char vertical, char cornor, int color)
{
    auto activeColor = this->view->GetActiveColorPair();
    this->view->SetActiveColorPair(color);
    this->DrawBox(r, horizontal, vertical, cornor);
    this->view->SetActiveColorPair(activeColor);
}

terminal::Canvas &terminal::Canvas::DrawBox(const util::Rectangle &r, char horizontal, int hColor, char vertical, int vColor, char cornor, int cColor)
{
    auto activeColor = this->view->GetActiveColorPair();
    auto tlc = this->clippedArea.Fit(util::Point(r.GetMinX(), r.GetMinY()));
    auto brc = this->clippedArea.Fit(util::Point(r.GetMaxX() - 1, r.GetMaxY() - 1));

    this->view->SetActiveColorPair(hColor);
    for (int x = tlc.GetX() + 1; x < brc.GetX(); x++)
    {
        this->view->Print(horizontal, x, tlc.GetY());
        this->view->Print(horizontal, x, brc.GetY());
    }

    this->view->SetActiveColorPair(vColor);
    for (int y = tlc.GetY() + 1; y < brc.GetY(); y++)
    {
        this->view->Print(vertical, tlc.GetX(), y);
        this->view->Print(vertical, brc.GetX(), y);
    }
    this->view->SetActiveColorPair(cColor);
    this->view->Print(cornor, tlc.GetX(), tlc.GetY());
    this->view->Print(cornor, brc.GetX(), tlc.GetY());
    this->view->Print(cornor, tlc.GetX(), brc.GetY());
    this->view->Print(cornor, brc.GetX(), brc.GetY());

    this->view->SetActiveColorPair(activeColor);

    return *this;
}

terminal::Canvas &terminal::Canvas::DrawBox(const util::Rectangle &r, char c)
{
    return this->DrawBox(r, c, c, c);
}

terminal::Canvas &terminal::Canvas::Fill(const util::Rectangle &r, char c)
{
    for (int x = r.GetMinX(); x < r.GetMaxX(); x++)
    {
        for (int y = r.GetMinY(); y < r.GetMaxY(); y++)
        {
            this->view->Print(c, x, y);
        }
    }

    return *this;
}

terminal::Canvas &terminal::Canvas::Clear(char c)
{
    return this->Fill(this->clippedArea, c);
}

terminal::Canvas &terminal::Canvas::Clear()
{
    return this->Clear(' ');
}

terminal::Canvas &terminal::Canvas::DrawString(const util::Point &p, const std::string &s)
{
    this->view->Print(s, p.GetX(), p.GetY());

    return *this;
}

terminal::Canvas &terminal::Canvas::DrawString(const util::Point &p, const std::string &s, int color)
{
    auto activeColor = this->view->GetActiveColorPair();
    this->view->SetActiveColorPair(color);
    this->DrawString(p, s);
    this->view->SetActiveColorPair(activeColor);
}

terminal::Canvas &terminal::Canvas::DrawString(const util::Point &p, const std::string &s, terminal::OutputAttribute attributes)
{
    auto activeAttributes = this->view->GetActiveAttributes();
    this->view->SetActiveAttributes(attributes);
    this->DrawString(p, s);
    this->view->SetActiveAttributes(activeAttributes);
}

terminal::Canvas &terminal::Canvas::DrawString(const util::Point &p, const std::string &s, int color, terminal::OutputAttribute attributes)
{

    auto activeAttributes = this->view->GetActiveAttributes();
    auto activeColor = this->view->GetActiveColorPair();
    this->view->SetActiveAttributes(attributes);
    this->view->SetActiveColorPair(color);
    this->DrawString(p, s);
    this->view->SetActiveAttributes(activeAttributes);
    this->view->SetActiveColorPair(activeColor);
}

const util::Dimension &terminal::Canvas::GetSize() const
{
    return this->size;
}

const util::Point &terminal::Canvas::GetOrigin() const
{
    return this->origin;
}

const util::Rectangle &terminal::Canvas::GetClippedArea() const
{
    return this->clippedArea;
}

void terminal::Canvas::SetOrigin(const util::Point &p)
{
    this->origin = p;
}

void terminal::Canvas::ClipArea(const util::Dimension &d)
{
    this->clippedArea = util::Rectangle(this->origin, d);
}

void terminal::Canvas::ClipArea(const util::Rectangle &p)
{
    this->clippedArea = p;
}

void terminal::Canvas::DisableClip()
{
    this->clippedArea = util::Rectangle(this->origin, this->size);
}

void terminal::Canvas::EnableAttribute(terminal::OutputAttribute a)
{
    this->view->AttributeOn(a);
}

void terminal::Canvas::DisableAttribute(terminal::OutputAttribute a)
{
    this->view->AttributeOff(a);
}

void terminal::Canvas::SetBackgroundColorPair(colorPairId_t c)
{
    this->view->SetBackgroundColorPair(c);
}

void terminal::Canvas::SetActiveColorPair(colorPairId_t index)
{
    this->view->SetActiveColorPair(index);
}


terminal::TerminalView *terminal::Canvas::GetView() const
{
    return this->view;
}

void terminal::Canvas::Flush()
{
    this->view->Flush();
}