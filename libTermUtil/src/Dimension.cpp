#include "Util.hpp"

terminal::Dimension::Dimension(int w, int h)
{
    this->SetWidth(w);
    this->SetHeight(h);
}

terminal::Dimension::Dimension(int w, float h)
{
    this->SetWidth(w);
    this->SetHeight(h);
}

terminal::Dimension::Dimension(float w, float h)
{
    this->SetWidth(w);
    this->SetHeight(h);
}

terminal::Dimension::Dimension(float w, int h)
{
    this->SetWidth(w);
    this->SetHeight(h);
}

util::Dimension terminal::Dimension::Convert(const util::Dimension &d) const
{
    return util::Dimension(this->Width(d), this->Height(d));
}

int terminal::Dimension::Width(const util::Dimension &d) const
{
    return this->width.isRelative ? this->width.value.relative * d.GetWidth() : this->width.value.absolute;
}

int terminal::Dimension::Height(const util::Dimension &d) const
{
    return this->height.isRelative ? this->height.value.relative * d.GetHeight() : this->height.value.absolute;
}

void terminal::Dimension::SetWidth(int w)
{
    this->width.isRelative = false;
    this->width.value.absolute = w;
}

void terminal::Dimension::SetWidth(float w)
{
    this->width.isRelative = true;
    this->width.value.absolute = w;
}

void terminal::Dimension::SetHeight(int h)
{
    this->height.isRelative = false;
    this->height.value.absolute = h;
}

void terminal::Dimension::SetHeight(float h)
{
    this->height.isRelative = true;
    this->height.value.absolute = h;
}
