#include "terminal/Canvas.hpp"
#include "data/Helper.hpp"
#include "Geometry.hpp"
#include "data/Io.hpp"

using util::Point;
using util::Rectangle;

terminal::Canvas::Canvas() : view(terminal::View::GetInstance()),
                             size(view->GetSize()),
                             origin(0, 0),
                             clippedArea(0, 0, this->size)
{
    this->view->SetLiveMode(false);
}

terminal::Canvas::Canvas(const Canvas &copy) : view(copy.view),
                                               size(copy.size),
                                               origin(copy.origin),
                                               clippedArea(copy.clippedArea)
{
}

int terminal::Canvas::X(int x)
{
    return this->origin.GetX() + x;
}

int terminal::Canvas::Y(int y)
{
    return this->origin.GetY() + y;
}

terminal::Canvas terminal::Canvas::GetSubCanvas(int x, int y, int w, int h)
{
    return this->GetSubCanvas(util::Rectangle(x, y, w, h));
}

terminal::Canvas terminal::Canvas::GetSubCanvas(const util::Rectangle &r)
{
    Canvas copy;

    auto intersection = util::Rectangle(0, 0, this->size).Intersect(r);

    copy.view = this->view;
    copy.size = intersection.GetSize();
    copy.clippedArea = intersection;
    copy.origin = copy.origin + r.GetLocation();

    return copy;
}

terminal::Canvas &terminal::Canvas::DrawVerticalLine(const Point &p, int length, char c)
{
    return this->DrawVerticalLine(p.GetX(), p.GetY(), length, c);
}

terminal::Canvas &terminal::Canvas::DrawVerticalLine(int x, int y, int length, char c)
{
    if (x >= this->clippedArea.GetMinX() && x <= this->clippedArea.GetMaxX())
    {
        int y0;
        int yn;

        if (length >= 0)
        {
            y0 = util::Max(y, this->clippedArea.GetMinY());
            yn = util::Min(y + length, this->clippedArea.GetMaxY());
        }
        else
        {
            y0 = util::Max(y + length, this->clippedArea.GetMinY());
            yn = util::Min(y, this->clippedArea.GetMaxY());
        }

        if (y0 > yn)
            return *this;

        x = this->X(x);
        y0 = this->Y(y0);
        yn = this->Y(yn);

        while (y0 < yn)
        {
            this->view->Print(c, x, y0);
            y0++;
        }
    }

    return *this;
}

terminal::Canvas &terminal::Canvas::DrawHorizontalLine(const Point &p, int length, char c)
{
    return this->DrawHorizontalLine(p.GetX(), p.GetY(), length, c);
}

terminal::Canvas &terminal::Canvas::DrawHorizontalLine(int x, int y, int length, char c)
{
    if (y >= this->clippedArea.GetMinY() && y <= this->clippedArea.GetMaxY())
    {
        int x0;
        int xn;

        if (length >= 0)
        {
            x0 = util::Max(x, this->clippedArea.GetMinX());
            xn = util::Min(x + length, this->clippedArea.GetMaxX());
        }
        else
        {
            x0 = util::Max(x + length, this->clippedArea.GetMinX());
            xn = util::Min(x, this->clippedArea.GetMaxX());
        }

        if (x0 > xn)
            return *this;

        y = this->Y(y);
        x0 = this->X(x0);
        xn = this->X(xn);

        while (x0 < xn)
        {
            this->view->Print(c, x0, y);
            x0++;
        }
    }

    return *this;
}

terminal::Canvas &terminal::Canvas::DrawBox(const Rectangle &r, char horizontal, char vertical, char corner)
{
    this->DrawHorizontalLine(r.GetMinX() + 1, r.GetMinY(), r.GetWidth() - 2, horizontal);
    this->DrawHorizontalLine(r.GetMinX() + 1, r.GetMaxY() - 1, r.GetWidth() - 2, horizontal);
    this->DrawVerticalLine(r.GetMinX(), r.GetMinY() + 1, r.GetHeight() - 2, vertical);
    this->DrawVerticalLine(r.GetMaxX() - 1, r.GetMinY() + 1, r.GetHeight() - 2, vertical);

    for (auto point : {r.TopLeft(),
                       r.TopRight() - util::Point(1, 0),
                       r.BottomRight() - util::Point(1, 1),
                       r.BottomLeft() - util::Point(0, 1)})
    {
        if (this->clippedArea.Contains(point))
            this->view->Print(corner, point.GetX(), point.GetY());
    }

    return *this;
}

terminal::Canvas &terminal::Canvas::DrawBox(int x, int y, int width, int height, char horizontal, char vertical, char corner)
{
    return this->DrawBox(util::Rectangle(x, y, width, height), horizontal, vertical, corner);
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
    auto targetArea = r.Intersect(this->clippedArea);

    int x, y;
    const int xn = r.GetMaxX() - 1;
    const int yn = r.GetMaxY() - 1;

    for (x = targetArea.GetMinX(); x < xn; x++)
        for (y = targetArea.GetMinY(); y < yn; y++)
            this->view->Print(c, x, y);

    return *this;
}

terminal::Canvas &terminal::Canvas::Fill(int x, int y, int width, int height, char c)
{
    return this->Fill(util::Rectangle(x, y, width, height), c);
}

terminal::Canvas &terminal::Canvas::Clear(char c)
{
    this->SetActiveColorPair(this->view->GetControlStyle(ControlStyleColor::ClearColor));

    int x, y;
    const int xn = this->size.GetWidth() - 1;
    const int yn = this->size.GetHeight() - 1;

    for (x = 0; x < xn; x++)
        for (y = 0; y < yn; y++)
            this->view->Print(c, x, y);
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
    int x0 = x;

    if (y > this->clippedArea.GetMaxY() || x > this->clippedArea.GetMaxX())
        return *this;

    for (size_t i = 0, n = s.length(); i < n; i++)
    {
        auto c = s[i];

        if (y < this->clippedArea.GetMinY() && c != '\n')
            continue;

        if (c == '\n')
        {
            y++;
            x = x0;

            if (y > this->clippedArea.GetMaxY())
                break;
        }
        else if (c == '\t')
        {
            auto remainingLength = this->clippedArea.GetMaxX() - x;

            while (remainingLength > 0)
            {
                this->view->Print(' ', this->X(x + remainingLength), this->Y(y));

                remainingLength--;
            }

            x += 4;
        }
        else if (c == '\r')
        {
            x = x0;
        }
        else
        {
            if (x >= this->clippedArea.GetMinX() && x < this->clippedArea.GetMaxX())
            {
                this->view->Print(c, this->X(x), this->Y(y));
            }

            x++;
        }
    }

    this->view->Print(s, x, y);

    return *this;
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
    this->clippedArea = util::Rectangle(0, 0, this->size).Intersect(r);

    return *this;
}

terminal::Canvas &terminal::Canvas::ClipArea(int x, int y, int w, int h)
{
    this->clippedArea = util::Rectangle(0, 0, this->size).Intersect(util::Rectangle(x, y, w, h));

    return *this;
}

terminal::Canvas &terminal::Canvas::DisableClip()
{
    this->clippedArea = util::Rectangle(0, 0, this->size);

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

terminal::View *terminal::Canvas::GetView() const
{
    return this->view;
}

void terminal::Canvas::Flush()
{
    this->view->Flush();
}