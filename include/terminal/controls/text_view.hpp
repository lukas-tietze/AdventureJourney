#pragma once

#include <string>
#include <vector>

#include "control_base.hpp"

namespace terminal
{
class text_view : public control_base
{
  private:
    std::vector<std::string> lines;
    void prepare_lines();

  public:
    text_view();
    text_view(const std::string &);
    virtual ~text_view();

    virtual void handle_key(key_input &);
    virtual void handle_mouse(mouse_input &);
    virtual void handle_bounds_changed(const util::rectangle &);
    virtual void handle_text_changed(const std::string &);

    virtual void render(canvas &);
};
} // namespace terminal
