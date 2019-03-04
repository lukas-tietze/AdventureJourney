#include <algorithm>

#include <pthread.h>

#include "Terminal.hpp"
#include "data/Io.hpp"

using util::Point;
using util::Rectangle;

terminal::Window::Window() : loop(true),
                             escapeKey(0),
                             hasEscapeKey(false),
                             screens(),
                             emptyScreen(new Screen()),
                             activeScreen(emptyScreen)
{
}

terminal::Window::~Window()
{
    delete this->emptyScreen;
}

void terminal::Window::Start(int escapeKey)
{
    this->escapeKey = escapeKey;
    this->hasEscapeKey = true;

    this->Start();
}

void terminal::Window::Start()
{
    auto view = View::GetInstance();
    auto canvas = Canvas();

    this->activeScreen->SetSize(view->GetSize());

    util::dbg.WriteLine("Initializing window! Size is %.", this->activeScreen->GetSize());

    this->activeScreen->RestoreLayout();
    this->activeScreen->Render(canvas);

    while (this->loop)
    {
        auto key = view->ReadKey();

        if (terminal::IsMouse(key))
        {
            MEVENT mouseEvent;

            if (getmouse(&mouseEvent) == OK)
            {
                MouseInput input;
                input.cx = mouseEvent.x;
                input.cy = mouseEvent.y;
                input.handled = false;
                input.action = static_cast<MouseAction>(mouseEvent.bstate);

                this->activeScreen->HandleMouse(input);
            }
        }
        else if (key == KEY_RESIZE || view->NeedsResize())
        {
            this->activeScreen->Invalidate();

            view->Resize();
            this->activeScreen->SetSize(view->GetSize());

            util::dbg.WriteLine("Initializing resize. New size is %.", view->GetSize());
        }
        else
        {
            KeyInput input;
            input.handled = false;
            input.key = key;
            input.specialKey = static_cast<Key>(key);

            this->activeScreen->HandleKey(input);

            if (!input.handled &&
                this->hasEscapeKey &&
                input.key == this->escapeKey)
            {
                this->loop = false;
            }
        }

        if (!this->activeScreen->IsValid())
            this->activeScreen->RestoreLayout();

        canvas.Clear();
        canvas.DisableClip();
        canvas.SetOrigin(0, 0);

        this->activeScreen->Render(canvas);

        canvas.Flush();
    }
}

void terminal::Window::Quit()
{
    this->loop = false;
}

void terminal::Window::AddScreen(Screen *s)
{
    if (std::find(this->screens.begin(), this->screens.end(), s) != this->screens.end())
    {
        s->AttachToWindow(this);
        this->screens.push_back(s);
    }
}

void terminal::Window::RemoveScreen(Screen *s)
{
    auto pos = std::find(this->screens.begin(), this->screens.end(), s);

    if (pos != this->screens.end())
    {
        (*pos)->DetachFromWindow();
        this->screens.erase(pos);
    }

    if (this->activeScreen == s)
    {
        if (this->screens.empty())
            this->activeScreen = this->emptyScreen;
        else if (pos++ < this->screens.end())
            this->SetActiveScreen(*(pos++));
        else if (pos-- >= this->screens.begin())
            this->SetActiveScreen(*(pos--));
    }
}

void terminal::Window::SetActiveScreen(Screen *s)
{
    auto pos = std::find(this->screens.begin(), this->screens.end(), s);

    if (pos != this->screens.end())
    {
        auto view = View::GetInstance();

        this->activeScreen = *pos;

        this->activeScreen->SetSize(view->GetSize());
    }
}
