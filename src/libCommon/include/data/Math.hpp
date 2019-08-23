#pragma once

#include <string>
#include <stdexcept>
#include <cstdarg>
#include <limits>

namespace util
{
template <class T>
T Crop(const T &x, const T &min, const T &max)
{
    if (x < min)
        return min;
    else if (x > max)
        return max;
    else
        return x;
}

template <class T>
T Max(const T &a, const T &b)
{
    return a > b ? a : b;
}

template <class TFirst, class... TArgs>
TFirst Max(const TFirst &a, const TFirst &b, const TArgs &... args)
{
    return a > b ? Max(a, args...) : Max(b, args...);
}

template <class T>
T Min(const T &a, const T &b)
{
    return a < b ? a : b;
}

template <class TFirst, class... TArgs>
TFirst Min(const TFirst &a, const TFirst &b, const TArgs &... args)
{
    return a < b ? Min(a, args...) : Min(b, args...);
}

template <class T>
T Max2(size_t n, ...)
{
    T max = std::numeric_limits<T>::min();
    T arg;

    va_list args;
    va_start(args, n);

    for (size_t i = 0; i < n; i++)
    {
        arg = va_arg(args, T);

        if (arg > max)
            max = arg;
    }

    va_end(args);

    return max;
}

template <class T>
T Min2(size_t n, ...)
{
    T min = std::numeric_limits<T>::max();
    T arg;

    va_list args;
    va_start(args, n);

    for (size_t i = 0; i < n; i++)
    {
        arg = va_arg(args, T);

        if (arg < min)
            min = arg;
    }

    va_end(args);

    return min;
}

template <class T>
T Mod(T v, T r)
{
    while (v > r)
        v -= r;

    return v;
}
} // namespace util