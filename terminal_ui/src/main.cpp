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

using util::Format;
using util::ToString;

namespace
{
bool running = true;
bool checkErrorDump = false;
char *DebugLocation = "debugfiles/backtrace.dump";
} // namespace

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

terminal::Screen *CreateStartScreen()
{
    auto res = new terminal::Screen();

    return res;
}

void RunComponentTest()
{
    terminal::Window w;

    auto startScreen = CreateStartScreen();

    w.AddScreen(startScreen);

    w.Start('q');

    delete startScreen;
}

void HandleSignal(util::SignalEventArgs &a)
{
    QuitAfterError();

    util::err.WriteLine("Received signal: %: %\n", a.signal, boost::stacktrace::stacktrace());
    std::quick_exit(-1);
}

void CheckErrorDump()
{
    if (checkErrorDump && boost::filesystem::exists(DebugLocation))
    {
        std::ifstream in(DebugLocation);

        if (in.good())
            util::out.WriteLine(boost::stacktrace::stacktrace::from_dump(in));

        util::out.WriteLine("Press any key to continue.");

        in.close();
        boost::filesystem::remove(DebugLocation);

        char c;
        std::scanf("%c", &c);
    }
}

void RerouteChannels()
{
    util::err.SetTarget(std::fopen("debugfiles/err.txt", "w"));
    util::out.SetTarget(std::fopen("debugfiles/out.txt", "w"));
    util::dbg.SetTarget(std::fopen("debugfiles/dbg.txt", "w"));
}

int main()
{
    util::EnableSignalHandling();
    util::StdSignalEvent() += HandleSignal;

    CheckErrorDump();
    RerouteChannels();

    try
    {
        RunComponentTest();
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