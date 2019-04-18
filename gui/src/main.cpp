#include "GlUtils.hpp"
#include "GlScreens.hpp"

int main()
{
    glutil::Init();

    auto screen = new gui::DummyScreen();

    screen->Show();

    glutil::Loop();

    delete screen;
    
    glutil::DestroyGlContext();
}