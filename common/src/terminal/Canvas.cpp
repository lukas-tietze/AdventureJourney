#include "terminal/Canvas.hpp"
#include "data/Helper.hpp"

using util::Point;
using util::Rectangle;

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

terminal::Canvas &terminal::Canvas::DrawVerticalLine(const Point &p, int length, char c)
{
    return this->DrawVerticalLine(p.GetX(), p.GetY(), length, c);
}

terminal::Canvas &terminal::Canvas::DrawVerticalLine(int x, int y, int length, char c)
{
    auto p = util::Point(x, y);
    auto start = this->clippedArea.Fit(p);
    auto end = this->clippedArea.Fit(p + util::Point(0, length));

    for (int y = start.GetY(); y < end.GetY(); y++)
    {
        this->view->Print(c, start.GetX(), y);
    }

    return *this;
}

terminal::Canvas &terminal::Canvas::DrawHorizontalLine(const Point &p, int length, char c)
{
    return this->DrawHorizontalLine(p.GetX(), p.GetY(), length, c);
}

terminal::Canvas &terminal::Canvas::DrawHorizontalLine(int x, int y, int length, char c)
{
    auto p = util::Point(x, y);
    auto start = this->clippedArea.Fit(p);
    auto end = this->clippedArea.Fit(p + util::Point(length, 0));

    for (int x = start.GetX(); x < end.GetX(); x++)
    {
        this->view->Print(c, x, start.GetY());
    }

    return *this;
}

terminal::Canvas &terminal::Canvas::DrawBox(const Rectangle &r, char horizontal, char vertical, char cornor)
{
    return this->DrawBox(r.GetX(), r.GetY(), r.GetWidth(), r.GetHeight(), horizontal, vertical, cornor);
}

terminal::Canvas &terminal::Canvas::DrawBox(int x, int y, int width, int height, char horizontal, char vertical, char cornor)
{
    auto tlc = this->clippedArea.Fit(util::Point(x, y));
    auto brc = this->clippedArea.Fit(util::Point(x + width - 1, y + height - 1));

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

terminal::Canvas &terminal::Canvas::DrawBox(const Rectangle &r, char c)
{
    return this->DrawBox(r.GetX(), r.GetY(), r.GetWidth(), r.GetHeight(), c);
}

terminal::Canvas &terminal::Canvas::DrawBox(int x, int y, int width, int height, char c)
{
    return this->DrawBox(x, y, width, height, c, c, c);
}

terminal::Canvas &terminal::Canvas::Fill(const Rectangle &r, char c)
{
    return this->Fill(r.GetX(), r.GetY(), r.GetWidth(), r.GetHeight(), c);
}

terminal::Canvas &terminal::Canvas::Fill(int x, int y, int width, int height, char c)
{
    for (int xp = x; xp < x + width; xp++)
    {
        for (int yp = y; yp < y + height; yp++)
        {
            this->view->Print(c, xp, yp);
        }
    }

    return *this;
}

terminal::Canvas &terminal::Canvas::Clear(char c)
{
    this->SetActiveColorPair(this->view->GetControlStyle(ControlStyleColor::ClearColor));

    return this->Fill(this->clippedArea.GetX(),
                      this->clippedArea.GetY(),
                      this->clippedArea.GetWidth(),
                      this->clippedArea.GetHeight(),
                      c);
}

terminal::Canvas &terminal::Canvas::Clear()
{
    return this->Clear(' ');
}

terminal::Canvas &terminal::Canvas::DrawString(const Point &p, const std::string &s)
{
    return this->DrawString(p.GetX(), p.GetY(), s);
}

terminal::Canvas &terminal::Canvas::DrawString(int x, int y, const std::string &s)
{
    this->view->Print(s, x, y);

    return *this;
}

terminal::Canvas &terminal::Canvas::DrawString(const Point &p, const std::string &s, terminal::OutputAttribute attributes)
{
    return this->DrawString(p.GetX(), p.GetY(), s, attributes);
}

terminal::Canvas &terminal::Canvas::DrawString(int x, int y, const std::string &s, terminal::OutputAttribute attributes)
{
    auto activeAttributes = this->view->GetActiveAttributes();
    this->view->SetActiveAttributes(attributes);
    this->DrawString(x, y, s);
    this->view->SetActiveAttributes(activeAttributes);
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

terminal::Canvas &terminal::Canvas::SetOrigin(const Point &p)
{
    this->origin = p;

    return *this;
}

terminal::Canvas &terminal::Canvas::SetOrigin(int x, int y)
{
    this->origin = util::Point(x, y);

    return *this;
}

terminal::Canvas &terminal::Canvas::ClipArea(const Rectangle &r)
{
    this->clippedArea = r;

    return *this;
}

terminal::Canvas &terminal::Canvas::ClipArea(int x, int y, int width, int height)
{
    this->clippedArea = util::Rectangle(x, y, width, height);

    return *this;
}

terminal::Canvas &terminal::Canvas::DisableClip()
{
    this->clippedArea = util::Rectangle(this->origin, this->size);

    return *this;
}

terminal::Canvas &terminal::Canvas::EnableAttribute(terminal::OutputAttribute a)
{
    this->view->AttributeOn(a);

    return *this;
}

terminal::Canvas &terminal::Canvas::DisableAttribute(terminal::OutputAttribute a)
{
    this->view->AttributeOff(a);

    return *this;
}

terminal::Canvas &terminal::Canvas::SetBackgroundColorPair(colorPairId_t c)
{
    this->view->SetBackgroundColorPair(c);

    return *this;
}

terminal::Canvas &terminal::Canvas::SetActiveColorPair(colorPairId_t index)
{
    this->view->SetActiveColorPair(index);

    return *this;
}

terminal::TerminalView *terminal::Canvas::GetView() const
{
    return this->view;
}

void terminal::Canvas::Flush()
{
    this->view->Flush();
}