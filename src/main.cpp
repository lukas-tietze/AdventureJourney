#include <cstdio>
#include <string>

#include "terminal.hpp"
#include "data/string.hpp"
#include "exception.hpp"
#include "data/rand.hpp"
#include "event.hpp"
#include "data/string.hpp"

short colors_schemes[5];
int mx, my, ms, mxw, myw;
bool running = true;

void quit()
{
    if (running)
    {
        terminal::terminal_view::delete_instance();
        endwin();
        running = false;
    }
}

void loop(terminal::terminal_view *v)
{
    terminal::canvas c(v);
    c.clear();
    c.draw_box(util::rectangle(1, 1, c.get_size().get_width() - 2, c.get_size().get_height() - 2), '-', '|', '+');
    c.draw_box(util::rectangle(0, 0, 4, 4), '-', '|', '+');

    c.draw_string(util::point(10, 3), "current terminal size is: " + util::to_string(c.get_size()));
    c.draw_string(util::point(10, 4), util::format("number of supported colors: %i (%i used)",
                                                   v->get_max_colors(),
                                                   v->get_used_colors()));
    c.draw_string(util::point(10, 5), util::format("number of supported color pairs: %i (%i used)",
                                                   v->get_max_color_pairs(),
                                                   v->get_used_color_pairs()));

    c.draw_string(util::point(10, 6), util::to_string(terminal::output_attribute::None), terminal::output_attribute::None);
    c.draw_string(util::point(10, 7), util::to_string(terminal::output_attribute::Standout), terminal::output_attribute::Standout);
    c.draw_string(util::point(10, 8), util::to_string(terminal::output_attribute::Underline), terminal::output_attribute::Underline);
    c.draw_string(util::point(10, 9), util::to_string(terminal::output_attribute::Reverse), terminal::output_attribute::Reverse);
    c.draw_string(util::point(10, 10), util::to_string(terminal::output_attribute::Blink), terminal::output_attribute::Blink);
    c.draw_string(util::point(10, 11), util::to_string(terminal::output_attribute::Dimmed), terminal::output_attribute::Dimmed);
    c.draw_string(util::point(10, 12), util::to_string(terminal::output_attribute::Bold), terminal::output_attribute::Bold);
    c.draw_string(util::point(10, 13), util::to_string(terminal::output_attribute::Protect), terminal::output_attribute::Protect);
    c.draw_string(util::point(10, 14), util::to_string(terminal::output_attribute::Invisible), terminal::output_attribute::Invisible);
    c.draw_string(util::point(10, 15), util::to_string(terminal::output_attribute::AlternatCharset), terminal::output_attribute::AlternatCharset);

    for (int i = 0; i < 5; i++)
    {
        c.draw_string(util::point(10, 16 + i), util::format("Color scheme %i (id=%i)", i, colors_schemes[i]), colors_schemes[i]);
    }

    c.draw_string(util::point(c.get_size().get_width() - 11, 5), util::format("MX: %i", mx));
    c.draw_string(util::point(c.get_size().get_width() - 11, 6), util::format("MY: %i", my));
    c.draw_string(util::point(c.get_size().get_width() - 11, 7), util::format("MXW: %i", mxw));
    c.draw_string(util::point(c.get_size().get_width() - 11, 8), util::format("MYW: %i", myw));
    c.draw_string(util::point(c.get_size().get_width() - 11, 9), util::format("MS: %i", ms));

    c.flush();
}

void run_component_test()
{
    terminal::terminal_view *v = terminal::terminal_view::get_instance();

    terminal::terminal_window w;

    auto cb = new terminal::checkbox();
    cb->set_bounds(util::rectangle(5, 5, 20, 3));
    cb->set_threeway_mode_enabled(false);
    cb->set_checked(true);

    auto bt = new terminal::button("Press Me!");
    bt->set_bounds(util::rectangle(5, 10, 20, 3));

    auto tv = new terminal::text_view(
        "01 2\n"\
        "3 45\n"\
        "");
    tv->set_bounds(util::rectangle(30, 5, 6, 40));

    auto tb = new terminal::textbox("Enter text here!");
    tb->set_bounds(util::rectangle(5, 15, 20, 3));

    w.add_control(cb);
    w.add_control(bt);
    w.add_control(tb);
    w.add_control(tv);

    w.start('q');
}

void run_function_test()
{
    terminal::terminal_view *v = terminal::terminal_view::get_instance();

    try
    {
        v->set_echo(false);
        v->set_input_mode(terminal::input_mode::BREAK);

        colors_schemes[0] = v->add_color_pair(util::colors::DarkGoldenrod1, util::colors::DarkSalmon);
        colors_schemes[1] = v->add_color_pair(util::colors::Firebrick3, util::colors::Goldenrod4);
        colors_schemes[2] = v->add_color_pair(util::colors::Gray39, util::colors::Grey12);
        colors_schemes[3] = v->add_color_pair(util::colors::LightBlue2, util::colors::Grey75);
        colors_schemes[4] = v->add_color_pair(util::colors::LightSeaGreen, util::colors::MediumOrchid3);

        int key;

        do
        {
            v->maximise();

            loop(v);

            key = v->read_key();

            if (key == '\t')
            {
                int buf = colors_schemes[0];

                for (int i = 0; i < 4; i++)
                {
                    colors_schemes[i] = colors_schemes[i + 1];
                }

                colors_schemes[4] = buf;
            }
            else if (key == 'c')
            {
                run_component_test();
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
    catch (const util::exception &e)
    {
        quit();
        std::printf("Error occurred!: %s\n", e.get_message().c_str());
    }
    catch (const std::exception &e)
    {
        quit();
        std::printf("Error occurred!: %s\n", e.what());
    }
    catch (...)
    {
        quit();
        std::printf("Unknown Error occurred!\n");
    }
}

void handle_signal(util::signal_event_args &a)
{
    quit();
    std::printf("Received signal: %s\n", util::to_string(a.signal).c_str());
    std::quick_exit(-1);
}

int main()
{
    util::enable_signal_handling();
    util::get_std_signal_event() += handle_signal;

    initscr();
    start_color();
    mousemask(ALL_MOUSE_EVENTS, nullptr);
    run_function_test();
    quit();

    return 0;
}