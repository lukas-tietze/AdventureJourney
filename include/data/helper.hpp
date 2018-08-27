#ifndef HELPER_HPP
#define HELPER_HPP

namespace util
{
template <class T>
void enable_flag(T &flag, const T &enabled)
{
    return static_cast<T>(static_cast<int>(flag) | static_cast<int>(enabled));
}

template <class T>
void disable_flag(T &flag, const T &disabled)
{
    return static_cast<T>(static_cast<int>(flag) & ~static_cast<int>(disabled));
}
} // namespace util

#endif /*HELPER_HPP*/