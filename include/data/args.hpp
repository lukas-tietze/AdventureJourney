#pragma once

#include <string>
#include "defs.hpp"

namespace util
{
class args
{
  public:
    args(int argc, char **argv);

    bool next(std::string &);
    bool has_next() const;
    bool next_int(int &t);
    bool has_next_int() const;
    bool next_uint(uint &);
    bool has_next_uint() const;
    bool next_double(double &);
    bool has_next_double() const;
    bool next_float(float &);
    bool has_next_float() const;
    bool next_bool(bool &);
    bool has_next_bool() const;

    const std::string &current();
    bool peek(std::string &target) const;

  private:
    int m_pos;
    int m_argc;
    char **m_argv;
    std::string m_last;

    bool next();
};

} // namespace util