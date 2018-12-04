#pragma once

namespace util
{
template <class T>
void EnableFlag(T &flag, const T &enabled)
{
    flag = static_cast<T>(static_cast<int>(flag) | static_cast<int>(enabled));
}

template <class T>
T EnableFlag(const T &flag, const T &enabled)
{
    return static_cast<T>(static_cast<int>(flag) | static_cast<int>(enabled));
}

template <class T>
void DisableFlag(T &flag, const T &disabled)
{
    flag = static_cast<T>(static_cast<int>(flag) & ~static_cast<int>(disabled));
}

template <class T>
T DisableFlag(const T &flag, const T &disabled)
{
    return static_cast<T>(static_cast<int>(flag) & ~static_cast<int>(disabled));
}
} // namespace util