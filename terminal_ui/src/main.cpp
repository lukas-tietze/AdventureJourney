#include <cstdio>
#include <string>

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
short ColorsSchemes[5];
int mx, my, ms, mxw, myw;
bool running = true;
} // namespace

void Quit()
{
    if (running)
    {
        terminal::TerminalView::DeleteInstance();
        running = false;
    }
}

void Loop(terminal::TerminalView *v)
{
    terminal::Canvas c(v);
    c.Clear();
    c.DrawBox(1, 1, c.GetSize().GetWidth() - 2, c.GetSize().GetHeight() - 2, '-', '|', '+');
    c.DrawBox(0, 0, 4, 4, '-', '|', '+');

    c.DrawString(10, 3, "current terminal size is: " + ToString(c.GetSize()));
    c.DrawString(10, 4, Format("number of supported colors: %i", v->GetMaxColors()));
    c.DrawString(10, 5, Format("number of supported color pairs: %i", v->GetMaxColorPairs()));

    c.DrawString(10, 6, ToString(terminal::OutputAttribute::None), terminal::OutputAttribute::None);
    c.DrawString(10, 7, ToString(terminal::OutputAttribute::Standout), terminal::OutputAttribute::Standout);
    c.DrawString(10, 8, ToString(terminal::OutputAttribute::Underline), terminal::OutputAttribute::Underline);
    c.DrawString(10, 9, ToString(terminal::OutputAttribute::Reverse), terminal::OutputAttribute::Reverse);
    c.DrawString(10, 10, ToString(terminal::OutputAttribute::Blink), terminal::OutputAttribute::Blink);
    c.DrawString(10, 11, ToString(terminal::OutputAttribute::Dimmed), terminal::OutputAttribute::Dimmed);
    c.DrawString(10, 12, ToString(terminal::OutputAttribute::Bold), terminal::OutputAttribute::Bold);
    c.DrawString(10, 13, ToString(terminal::OutputAttribute::Protect), terminal::OutputAttribute::Protect);
    c.DrawString(10, 14, ToString(terminal::OutputAttribute::Invisible), terminal::OutputAttribute::Invisible);
    c.DrawString(10, 15, ToString(terminal::OutputAttribute::AlternatCharset), terminal::OutputAttribute::AlternatCharset);

    for (int i = 0; i < 5; i++)
    {
        c.SetActiveColorPair(ColorsSchemes[i])
            .DrawString(10, 16 + i, Format("Color scheme %i (id=%i)", i, ColorsSchemes[i]));
    }

    c.DrawString(c.GetSize().GetWidth() - 11, 5, Format("MX: %i", mx));
    c.DrawString(c.GetSize().GetWidth() - 11, 6, Format("MY: %i", my));
    c.DrawString(c.GetSize().GetWidth() - 11, 7, Format("MXW: %i", mxw));
    c.DrawString(c.GetSize().GetWidth() - 11, 8, Format("MYW: %i", myw));
    c.DrawString(c.GetSize().GetWidth() - 11, 9, Format("MS: %i", ms));

    c.Flush();
}

void RunComponentTest()
{
    terminal::TerminalWindow w;

    auto cb = new terminal::Checkbox();
    cb->SetBounds(5, 5, 20, 3);
    cb->SetThreewayModeEnabled(false);
    cb->SetChecked(true);

    auto bt = new terminal::Button("Press Me!");
    bt->SetBounds(5, 10, 20, 3);

    auto tv = new terminal::TextView("0123456789101112");
    tv->SetBounds(0, 0, 6, 6);

    auto tb = new terminal::Textbox();
    tb->SetBounds(10, 0, 10, 3);

    auto db = new terminal::DebugBox();
    db->SetBounds(20, 15, 20, 3);

    w.Add(cb);
    w.Add(bt);
    w.Add(tv);
    w.Add(tb);
    w.Add(db);

    w.Start('q');
}

void RunFunctionTest()
{
    terminal::TerminalView *v = terminal::TerminalView::GetInstance();

    try
    {
        v->SetEcho(false);
        v->SetInputMode(terminal::InputMode::Break);

        int key;

        do
        {
            v->Maximise();

            Loop(v);

            key = v->ReadKey();

            if (key == '\t')
            {
                int buf = ColorsSchemes[0];

                for (int i = 0; i < 4; i++)
                {
                    ColorsSchemes[i] = ColorsSchemes[i + 1];
                }

                ColorsSchemes[4] = buf;
            }
            else if (key == 'c')
            {
                RunComponentTest();
            }
            else if (key == KEY_MOUSE)
            {
                MEVENT mouseEvent;
                if (getmouse(&mouseEvent) == OK)
                {
                    mx = mxw = mouseEvent.x;
                    my = myw = mouseEvent.y;
                    ms = mouseEvent.bstate;
                    mouse_trafo(&mxw, &myw, false);
                }
            }

        } while (running && key != 'q');
    }
    catch (const util::Exception &e)
    {
        Quit();
        util::err.WriteLine("util::Exception occurred!: %\nAt %\n", e.GetMessage(), e.GetStacktrace());
    }
    catch (const std::exception &e)
    {
        Quit();
        util::err.WriteLine("std::exception occurred!: %\n", e.what());
    }
    catch (...)
    {
        Quit();
        util::err.WriteLine("Unknown error occurred!\n");
    }
}

void HandleSignal(util::SignalEventArgs &a)
{
    Quit();

    util::err.WriteLine("Received signal: %: %\n", a.signal, boost::stacktrace::stacktrace());
    std::quick_exit(-1);
}

int main()
{
    util::EnableSignalHandling();
    util::StdSignalEvent() += HandleSignal;

    RunFunctionTest();
    Quit();

    return 0;
}