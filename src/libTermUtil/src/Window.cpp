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
    this->activeScreen = nullptr;

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
    auto mouseX = 0;
    auto mouseY = 0;
    auto view = View::GetInstance();
    auto canvas = Canvas();

    this->activeScreen->SetSize(view->GetSize());
    this->activeScreen->RestoreLayout();
    this->activeScreen->Render(canvas);

    util::dbg.WriteLine("Initialized window! Size is %.", this->activeScreen->GetSize());

    while (this->loop)
    {
        auto key = view->ReadKey();

        if (terminal::IsMouse(key))
        {
            MEVENT mouseEvent;

            if (getmouse(&mouseEvent) == OK)
            {
                MouseInput input;
                input.x = mouseEvent.x;
                input.y = mouseEvent.y;
                input.screenX = mouseEvent.x;
                input.screenY = mouseEvent.y;
                input.handled = false;
                input.action = static_cast<MouseAction>(mouseEvent.bstate);

                mouseX = mouseEvent.x;
                mouseY = mouseEvent.y;

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
            input.key = key;
            input.specialKey = static_cast<Key>(key);
            input.handled = false;

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
        canvas.Reset();

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
    if (std::find(this->screens.begin(), this->screens.end(), s) == this->screens.end())
    {
        s->AttachToWindow(this);
        this->screens.push_back(s);

        util::dbg.WriteLine("Window [%]: added screen [%].", this, s);
    }
}

void terminal::Window::RemoveScreen(Screen *s)
{
    auto pos = std::find(this->screens.begin(), this->screens.end(), s);

    if (pos != this->screens.end())
    {
        (*pos)->DetachFromWindow();
        this->screens.erase(pos);

        util::dbg.WriteLine("Window [%]: removed screen [%].", this, s);
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
        if (this->activeScreen != nullptr)
            this->activeScreen->HandleHide();

        auto view = View::GetInstance();

        this->activeScreen = *pos;
        this->activeScreen->HandleShow();
        this->activeScreen->Invalidate();
        this->activeScreen->SetSize(view->GetSize());
        this->activeScreen->RestoreLayout();

        util::dbg.WriteLine("Window [%]: [%] is now the active screen.", this, *pos);
    }
    else
    {
        util::dbg.WriteLine("Window [%]: could not change active screen, screen [%] is unknown.", this, s);
    }
}

void terminal::Window::Blank()
{
    this->activeScreen->HandleHide();
    this->activeScreen = this->emptyScreen;

    util::dbg.WriteLine("Window [%]: blanking screen.", this);
}
