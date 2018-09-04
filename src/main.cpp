#include <cstdio>
#include <string>

#include "terminal.hpp"
#include "data/string.hpp"
#include "exception.hpp"
#include "data/rand.hpp"

short colors_schemes[5];
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

void print_attribute(int line, terminal::output_attribute a, terminal::canvas &c)
{
    c.enable_attribute(a);
    c.draw_string(util::point(10, line), util::to_string(a));
    c.disable_attribute(a);
}

int loop(terminal::terminal_view *v)
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

    print_attribute(6, terminal::output_attribute::None, c);
    print_attribute(7, terminal::output_attribute::Standout, c);
    print_attribute(8, terminal::output_attribute::Underline, c);
    print_attribute(9, terminal::output_attribute::Reverse, c);
    print_attribute(10, terminal::output_attribute::Blink, c);
    print_attribute(11, terminal::output_attribute::Dimmed, c);
    print_attribute(12, terminal::output_attribute::Bold, c);
    print_attribute(13, terminal::output_attribute::Protect, c);
    print_attribute(14, terminal::output_attribute::Invisible, c);
    print_attribute(15, terminal::output_attribute::AlternatCharset, c);

    for (int i = 0; i < 5; i++)
    {
        c.set_active_color_pair(colors_schemes[i]);
        c.draw_string(util::point(10, 16 + i), util::format("Color scheme %i (id=%i)", i, colors_schemes[i]));
    }

    c.draw_string(util::point(10, 21), util::format("red is (%i, %i, %i)",
                                                    util::colors::BasicRed.red(),
                                                    util::colors::BasicRed.green(),
                                                    util::colors::BasicRed.blue()));

    c.flush();
}

int run()
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

            if (key == 'c')
            {
                int buf = colors_schemes[0];

                for (int i = 0; i < 4; i++)
                {
                    colors_schemes[i] = colors_schemes[i + 1];
                }

                colors_schemes[5] = buf;
            }

        } while (key != 'q');
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

int main(int argc, char **argv)
{
    initscr();
    start_color();
    run();
    quit();
    return 0;
}