#include "GlUtils.hpp"
#include "GlScreens.hpp"
#include "Exception.hpp"
#include "data/Io.hpp"

#include <stdexcept>

int main()
{
    glutil::Init();

    auto screen = new gui::DummyObjectScreen();

    screen->Show();

    try
    {
        glutil::Loop();
    }
    catch (util::Exception &e)
    {
        util::err.WriteLine("Exception occurred. Message: %\nStacktrace: %", e.GetMessage(), e.GetStacktrace());
    }
    catch (std::exception &e)
    {
        util::err.WriteLine("Exception occurred. Message: %", e.what());
    }
    catch (...)
    {
        util::err.WriteLine("unknown exception occurred.");
    }

    delete screen;

    glutil::DestroyGlContext();
}