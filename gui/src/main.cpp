#include "GlUtils.hpp"

int main()
{
    glutil::Init();
    glutil::Loop();
    glutil::Quit();
    glutil::DestroyGlContext();
}