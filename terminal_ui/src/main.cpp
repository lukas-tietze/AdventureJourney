#include <cstdio>
#include <string>

#include "Terminal.hpp"
#include "data/String.hpp"
#include "Exception.hpp"
#include "data/Random.hpp"
#include "Event.hpp"
#include "data/String.hpp"

short ColorsSchemes[5];
int mx, my, ms, mxw, myw;
bool running = true;

void Quit()
{
    if (running)
    {
        terminal::TerminalView::DeleteInstance();
        endwin();
        running = false;
    }
}

void Loop(terminal::TerminalView *v)
{
    terminal::Canvas c(v);
    c.Clear();
    c.DrawBox(util::Rectangle(1, 1, c.GetSize().GetWidth() - 2, c.GetSize().GetHeight() - 2), '-', '|', '+');
    c.DrawBox(util::Rectangle(0, 0, 4, 4), '-', '|', '+');

    c.DrawString(util::Point(10, 3), "current terminal size is: " + util::ToString(c.GetSize()));
    c.DrawString(util::Point(10, 4), util::Format("number of supported colors: %i (%i used)",
                                                   v->GetMaxColors(),
                                                   v->GetUsedColors()));
    c.DrawString(util::Point(10, 5), util::Format("number of supported color pairs: %i (%i used)",
                                                   v->GetMaxColorPairs(),
                                                   v->GetUsedColorPairs()));

    c.DrawString(util::Point(10, 6), util::ToString(terminal::OutputAttribute::None), terminal::OutputAttribute::None);
    c.DrawString(util::Point(10, 7), util::ToString(terminal::OutputAttribute::Standout), terminal::OutputAttribute::Standout);
    c.DrawString(util::Point(10, 8), util::ToString(terminal::OutputAttribute::Underline), terminal::OutputAttribute::Underline);
    c.DrawString(util::Point(10, 9), util::ToString(terminal::OutputAttribute::Reverse), terminal::OutputAttribute::Reverse);
    c.DrawString(util::Point(10, 10), util::ToString(terminal::OutputAttribute::Blink), terminal::OutputAttribute::Blink);
    c.DrawString(util::Point(10, 11), util::ToString(terminal::OutputAttribute::Dimmed), terminal::OutputAttribute::Dimmed);
    c.DrawString(util::Point(10, 12), util::ToString(terminal::OutputAttribute::Bold), terminal::OutputAttribute::Bold);
    c.DrawString(util::Point(10, 13), util::ToString(terminal::OutputAttribute::Protect), terminal::OutputAttribute::Protect);
    c.DrawString(util::Point(10, 14), util::ToString(terminal::OutputAttribute::Invisible), terminal::OutputAttribute::Invisible);
    c.DrawString(util::Point(10, 15), util::ToString(terminal::OutputAttribute::AlternatCharset), terminal::OutputAttribute::AlternatCharset);

    for (int i = 0; i < 5; i++)
    {
        c.DrawString(util::Point(10, 16 + i), util::Format("Color scheme %i (id=%i)", i, ColorsSchemes[i]), ColorsSchemes[i]);
    }

    c.DrawString(util::Point(c.GetSize().GetWidth() - 11, 5), util::Format("MX: %i", mx));
    c.DrawString(util::Point(c.GetSize().GetWidth() - 11, 6), util::Format("MY: %i", my));
    c.DrawString(util::Point(c.GetSize().GetWidth() - 11, 7), util::Format("MXW: %i", mxw));
    c.DrawString(util::Point(c.GetSize().GetWidth() - 11, 8), util::Format("MYW: %i", myw));
    c.DrawString(util::Point(c.GetSize().GetWidth() - 11, 9), util::Format("MS: %i", ms));

    c.Flush();
}

void RunComponentTest()
{
    terminal::TerminalWindow w;

    auto cb = new terminal::Checkbox();
    cb->SetBounds(util::Rectangle(5, 5, 20, 3));
    cb->SetThreewayModeEnabled(false);
    cb->SetChecked(true);

    auto bt = new terminal::Button("Press Me!");
    bt->SetBounds(util::Rectangle(5, 10, 20, 3));

    auto tv = new terminal::TextView(
        "01 2\n"\
        "3 45\n"\
        "678 90");
    tv->SetBounds(util::Rectangle(5, 5, 40, 40));

    auto tb = new terminal::Textbox("Enter text here!");
    tb->SetBounds(util::Rectangle(5, 15, 20, 3));

    // w.AddControl(cb);
    // w.AddControl(bt);
    // w.AddControl(tb);
    w.AddControl(tv);

    w.Start('q');
}

void RunFunctionTest()
{
    terminal::TerminalView *v = terminal::TerminalView::GetInstance();

    try
    {
        v->SetEcho(false);
        v->SetInputMode(terminal::InputMode::Break);

        ColorsSchemes[0] = v->AddColorPair(util::colors::DarkGoldenrod1, util::colors::DarkSalmon);
        ColorsSchemes[1] = v->AddColorPair(util::colors::Firebrick3, util::colors::Goldenrod4);
        ColorsSchemes[2] = v->AddColorPair(util::colors::Gray39, util::colors::Grey12);
        ColorsSchemes[3] = v->AddColorPair(util::colors::LightBlue2, util::colors::Grey75);
        ColorsSchemes[4] = v->AddColorPair(util::colors::LightSeaGreen, util::colors::MediumOrchid3);

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
        std::printf("Error occurred!: %s\n", e.GetMessage().c_str());
    }
    catch (const std::exception &e)
    {
        Quit();
        std::printf("Error occurred!: %s\n", e.what());
    }
    catch (...)
    {
        Quit();
        std::printf("Unknown error occurred!\n");
    }
}

void HandleSignal(util::SignalEventArgs &a)
{
    Quit();
    std::printf("Received signal: %s\n", util::ToString(a.signal).c_str());
    std::quick_exit(-1);
}

int main()
{
    util::EnableSignalHandling();
    util::StdSignalEvent() += HandleSignal;

    initscr();
    start_color();
    mousemask(ALL_MOUSE_EVENTS, nullptr);
    RunFunctionTest();
    Quit();

    return 0;
}