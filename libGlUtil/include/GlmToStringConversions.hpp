#pragma once

#include <ostream>
#include "glm/glm.hpp"

namespace glm
{
template <int N, class TData, glm::qualifier Q>
std::ostream &operator<<(std::ostream &s, const glm::vec<N, TData, Q> &vec)
{
    s << '(' << vec[0];

    for (int i = 1; i < N; i++)
        s << ", " << vec[i];

    s << ')';

    return s;
}

template <int C, int R, class TData, glm::qualifier Q>
std::ostream &operator<<(std::ostream &s, const glm::mat<C, R, TData, Q> &mat)
{
    s << '[' << mat[0][0];

    for (int c = 1; c < C; c++)
        s << ", " << mat[c][0];

    for (int r = 1; r < R; r++)
    {
        s << "| " << mat[0][r];

        for (int c = 1; c < C; c++)
            s << ", " << mat[c][r];
    }

    s << ']';

    return s;
}
} // namespace glm