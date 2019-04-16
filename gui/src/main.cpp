#include "GlUtils.hpp"
#include "GlScreens.hpp"

int main()
{
    glutil::Init();
    glutil::Loop();

    auto screen = new gui::DummyScreen();

    screen->Show();

    delete screen;

    glutil::Quit();
    glutil::DestroyGlContext();
}