#pragma once

#include <string>
#include "Defs.hpp"

namespace util
{
class Args
{
  public:
    Args(int argc, char **argv);

    bool Next(std::string &);
    bool HasNext() const;
    bool NextInt(int &t);
    bool HasNextInt() const;
    bool NextUint(uint &);
    bool HasNextUint() const;
    bool NextDouble(double &);
    bool HasNextDouble() const;
    bool NextFloat(float &);
    bool HasNextFloat() const;
    bool NextBool(bool &);
    bool HasNextBool() const;

    const std::string &Current();
    bool Peek(std::string &target) const;

  private:
    int pos;
    int argc;
    char **argv;
    std::string last;

    bool Next();
};
} // namespace util