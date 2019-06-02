#include <stdexcept>

#include "Exception.hpp"
#include "GlUtils.hpp"
#include "GlScreens.hpp"
#include "data/Io.hpp"

int main()
{
    if (!glutil::Init())
    {
        util::dbg.WriteLine("Failed to Init GL! Exiting...");
        return 1;
    }

    try
    {
        auto screen = new gui::PlanetScreen();

        screen->Show();
        
        glutil::Loop();
        
        delete screen;
    }
    catch (util::Exception &e)
    {
        util::err.WriteLine("Exception occurred. Message: %\nStacktrace: %", e.what(), e.GetStacktrace());
    }
    catch (std::exception &e)
    {
        util::err.WriteLine("Exception occurred. Message: %", e.what());
    }
    catch (...)
    {
        util::err.WriteLine("unknown exception occurred.");
    }

    glutil::DestroyGlContext();
}