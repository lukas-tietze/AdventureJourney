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
    mouse_action action;
    bool handled;
};

class container_base;

class control_base
{
  private:
    util::rectangle bounds;
    util::dimension minimum_size;
    util::dimension maximum_size;
    control_base *parent;
    int z_index;
    bool has_focus;
    int tab_index;
    std::string text;
    bool visible;
    int text_style;

  protected:
    void set_bounds_core(const util::rectangle &);
    void set_z_index_core(int);
    void set_text_core(const std::string &);
    void set_visibility_core(bool visible);
    void set_tab_index_core(int);
    void set_min_size_core(const util::dimension &);
    void set_max_size_core(const util::dimension &);

    bool validate_bounds(util::rectangle &);

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
    const std::string &get_text() const;
    void set_text(const std::string &);
    bool is_visible() const;
    void set_visibility(bool visible);
    int get_tab_index() const;
    void set_tab_index(int);
    const util::dimension &get_min_size() const;
    const util::dimension &get_max_size() const;
    void set_min_size(const util::dimension &);
    void set_max_size(const util::dimension &);

    virtual void handle_z_index_changed();
    virtual void handle_tab_index_changed();
    virtual void handle_bounds_changed();
    virtual void handle_text_changed();

    virtual void handle_focus_aquired();
    virtual void handle_focus_lost();
    virtual void handle_key(key_input &);
    virtual void handle_mouse(mouse_input &);
    virtual void handle_add_to_control(container_base *);

    virtual void render(canvas &) = 0;
};
} // namespace terminal