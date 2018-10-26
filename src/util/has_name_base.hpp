#pragma once

#include <string>

namespace logic
{
class has_name_base
{
  private:
    std::string name;

  protected:
    std::string &get_name();
    void set_name(const std::string &);

    has_name_base(const has_name_base &);
    has_name_base(const std::string &);
    has_name_base();

  public:
    const std::string get_name() const;
};
} // namespace logic