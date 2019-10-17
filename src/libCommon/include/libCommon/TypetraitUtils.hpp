#pragma once

namespace util
{
template <typename T, typename = void>
struct is_iterator
{
    static constexpr bool value = false;
};

template <typename T>
struct is_iterator<T, typename std::enable_if<!std::is_same<typename std::iterator_traits<T>::value_type, void>::value>::type>
{
    static constexpr bool value = true;
};

template<typename T>
inline constexpr bool is_iterator_v = util::is_iterator<T>::value;
} // namespace util
