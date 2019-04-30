#include "GlUtils.hpp"

glutil::Screen::~Screen()
{
}

void glutil::Screen::Render()
{
}

void glutil::Screen::Update(double)
{
}

void glutil::Screen::OnShow()
{
}

void glutil::Screen::OnHide()
{
}

void glutil::Screen::Show()
{
    glutil::RequestNextScreen(this);
}
