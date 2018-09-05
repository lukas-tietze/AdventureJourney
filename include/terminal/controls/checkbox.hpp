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
    checkbox(const std::string &);
    checkbox(const std::string &, bool checked);

    bool is_checked() const;
    void set_checked(bool checked);
    check_state get_check_state() const;
    void set_check_state(check_state) const;
    void set_threeway_mode_enabled(bool);
    bool is_threeeway_mode_enabled() const;

    virtual void handle_focus_aquired();
    virtual void handle_focus_lost();
    virtual void handle_key(key_input &);
    virtual void handle_mouse(mouse_input &);
    virtual void handle_add_to_control(control_base *);

    virtual void render(const util::rectangle &, canvas &);
};
} // namespace terminal