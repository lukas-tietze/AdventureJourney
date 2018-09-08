#pragma once

#include "control_base.hpp"

namespace terminal
{
enum class check_state
{
    Checked,
    Midway,
    Unchecked,
};

class checkbox : public terminal::control_base
{
  private:
    check_state state;
    bool threeway_mode;

  public:
    checkbox();

    bool is_checked() const;
    void set_checked(bool checked);
    check_state get_check_state() const;
    void set_check_state(check_state);
    void set_threeway_mode_enabled(bool);
    bool is_threeeway_mode_enabled() const;

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