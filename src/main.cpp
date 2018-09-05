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

                colors_schemes[4] = buf;
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