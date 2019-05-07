#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include "data/String.hpp"
#include "data/Io.hpp"
#include "glad/glad.h"

namespace
{
namespace nsp
{
class Foo
{
  public:
    template <int T>
    int bar();
};
} // namespace nsp
} // namespace

template <>
int nsp::Foo::bar<1>()
{
    return 0;
}

template <int T>
int nsp::Foo::bar()
{
    return T;
}

int main()
{
    util::out.WriteLine("bar<2> is %", nsp::Foo().bar<2>());
    util::out.WriteLine("bar<1> is %", nsp::Foo().bar<1>());
}