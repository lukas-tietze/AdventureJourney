#pragma once

#include "terminal/canvas.hpp"
#include "geometry.hpp"

namespace terminal
{
struct key_input
{
    int key;
    bool handled;
};

struct mouse_input
{
    int cx;
    int cy;
    int action;
    bool handled;
};

class container_base;

class control_base
{
  private:
    util::rectangle bounds;
    control_base *parent;
    int z_index;
    bool has_focus;
    int tab_index;
    std::string text;
    bool visible;

  public:
    control_base();
    virtual ~control_base();

    struct z_index_sorter
    {
        int operator()(const control_base &, const control_base &);
    };

    struct tab_index_sorter
    {
        int operator()(const control_base &, const control_base &);
    };

    control_base *get_parent();
    const control_base *get_parent() const;

    bool has_parent() const;
    const util::rectangle &get_bounds() const;
    void set_bounds(const util::rectangle &);
    void set_z_index(int);
    int get_z_index() const;
    std::string &get_text();
    const std::string &get_text() const;
    void set_text(const std::string &);
    bool is_visible() const;
    void set_visibility(bool visible);
    int get_tab_index() const;
    void set_tab_index(int);

    virtual void handle_focus_aquired();
    virtual void handle_focus_lost();
    virtual void handle_key(key_input &);
    virtual void handle_mouse(mouse_input &);
    virtual void handle_add_to_control(container_base *);
    virtual void handle_z_index_changed(int);
    virtual void handle_tab_index_changed(int);

    virtual void render(canvas &);
};
} // namespace terminal