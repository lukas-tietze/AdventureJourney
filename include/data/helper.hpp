#ifndef HELPER_HPP
#define HELPER_HPP

namespace util
{
template <class T>
void enable_flag(T &flag, const T &enabled)
{
    flag = static_cast<T>(static_cast<int>(flag) | static_cast<int>(enabled));
}

template <class T>
T enable_flag(const T &flag, const T &enabled)
{
    return static_cast<T>(static_cast<int>(flag) | static_cast<int>(enabled));
}

template <class T>
void disable_flag(T &flag, const T &disabled)
{
    flag = static_cast<T>(static_cast<int>(flag) & ~static_cast<int>(disabled));
}

template <class T>
T disable_flag(const T &flag, const T &disabled)
{
    return static_cast<T>(static_cast<int>(flag) & ~static_cast<int>(disabled));
}
} // namespace util

#endif /*HELPER_HPP*/