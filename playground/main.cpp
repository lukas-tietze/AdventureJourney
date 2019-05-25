#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

// #include "data/String.hpp"
// #include "data/Io.hpp"
// #include "glad/glad.h"
// #include "DummyData.hpp"

namespace
{
struct CMP
{
    int operator()(const std::string &a, const std::string &b)
    {
        int res = 0;

        for (size_t i = 0; i < a.length() && i < b.length() && res == 0; i++)
        {
            res = a[i] - b[i];
        }

        if (res == 0)
            return a.length() - b.length();

        return res;
    }
};
} // namespace

int main()
{
    std::vector<std::string> v =
        {
            "=",
            "!",
            "!=",
            "==",
            "!===",
            "====",
            "*",
            "*=",
            "+",
            "+=",
        };

    std::sort(v.begin(), v.end(), CMP());

    for (const auto &val : v)
    {
        std::cout << val << std::endl;
    };
}