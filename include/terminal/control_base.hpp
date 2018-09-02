#ifndef TERMINAL_CONTROL_BASE_HPP
#define TERMINAL_CONTROL_BASE_HPP

#include "canvas.hpp"
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
    int button;
    bool handled;
};

class control_base
{
  private:
    util::rectangle bounds;
    control_base *parent;
    int z_index;
    bool has_focus;
    std::string text;

  public:
    control_base();
    virtual ~control_base();

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

    virtual void handle_focus_aquired();
    virtual void handle_focus_lost();
    virtual void handle_key(key_input &);
    virtual void handle_mouse(mouse_input &);
    virtual void handle_add_to_control(control_base *);

    virtual void render(const util::rectangle &, canvas &);
};
} // namespace terminal

#endif /*TERMINAL_CONTROL_BASE_HPP*/