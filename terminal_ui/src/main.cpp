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
        terminal::TerminalView::DeleteInstance();
        running = false;
    }
}

void QuitAfterError()
{
    boost::stacktrace::safe_dump_to(DebugLocation);
    Quit();
}

void RunComponentTest()
{
    terminal::TerminalWindow w;

    auto container = new terminal::FrameContainer();
    container->SetBorderEnabled(true);
    container->SetAutoSizeMode(terminal::AutoSizeMode::Fill);
    container->SetSize(20, 20);
    container->SetLocation(0, 0);

    w.Add(container);

    auto textLeft = new terminal::Textbox();
    textLeft->SetSize(util::Dimension());

    w.Start('q');
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

int main()
{
    util::EnableSignalHandling();
    util::StdSignalEvent() += HandleSignal;

    CheckErrorDump();

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