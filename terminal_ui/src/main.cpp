#include <cstdio>
#include <string>
#include <boost/stacktrace.hpp>
#include <boost/filesystem.hpp>

#include "Terminal.hpp"
#include "data/String.hpp"
#include "Exception.hpp"
#include "data/Random.hpp"
#include "Event.hpp"
#include "data/String.hpp"
#include "data/Io.hpp"
#include "Screens.hpp"

using util::Format;
using util::ToString;

namespace
{
bool running = true;
char *DebugLocation = "debugfiles/backtrace.dump";

void Quit()
{
    if (running)
    {
        terminal::View::DeleteInstance();
        running = false;
    }
}

void QuitAfterError()
{
    boost::stacktrace::safe_dump_to(DebugLocation);
    Quit();
}

void Start()
{
    terminal::Window w;

    screens::Start = screens::CreateStartScreen();
    screens::Menu = screens::CreateMenuScreen();

    w.AddScreen(screens::Start);
    w.AddScreen(screens::Menu);

    w.Start('q');

    delete screens::Start;
    delete screens::Menu;
}

void HandleSignal(int sig)
{
    QuitAfterError();

    util::err.WriteLine("Received Signal %:\n %\n", sig, boost::stacktrace::stacktrace());

    std::quick_exit(-1);
}

void CheckErrorDump()
{
    if (boost::filesystem::exists(DebugLocation))
    {
        try
        {
            std::ifstream in;

            in.open(DebugLocation);

            if (in.is_open() && in.good())
            {
                util::out.WriteLine(boost::stacktrace::stacktrace::from_dump(in));
            }

            in.close();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        boost::filesystem::remove(DebugLocation);

        util::WaitForKeyPress("Press [Enter] to continue.");
    }
}

void RerouteChannels()
{
    util::err.SetTarget(std::fopen("debugfiles/err.txt", "w"));
    util::out.SetTarget(std::fopen("debugfiles/out.txt", "w"));
    util::dbg.SetTarget(std::fopen("debugfiles/dbg.txt", "w"));

    util::err.SetShowTime(true);
    util::out.SetShowTime(true);
    util::dbg.SetShowTime(true);
}

void CreateSignalListeners()
{
    std::signal(SIGABRT, HandleSignal);
    std::signal(SIGFPE, HandleSignal);
    std::signal(SIGILL, HandleSignal);
    std::signal(SIGINT, HandleSignal);
    std::signal(SIGSEGV, HandleSignal);
    std::signal(SIGTERM, HandleSignal);
}
} // namespace

int main()
{
    CreateSignalListeners();
    CheckErrorDump();
    RerouteChannels();

    try
    {
        Start();
    }
    catch (const util::Exception &e)
    {
        QuitAfterError();
        util::err.WriteLine("util::Exception occurred!: %\nAt %\n", e.GetMessage(), e.GetStacktrace());
    }
    catch (const std::exception &e)
    {
        QuitAfterError();
        util::err.WriteLine("std::exception occurred!: %\n", e.what());
    }
    catch (...)
    {
        QuitAfterError();
        util::err.WriteLine("Unknown error occurred!\n");
    }

    Quit();

    return 0;
}