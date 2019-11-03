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

template<typename TLhs, typename ...TRhs>
struct is_one_of
{
	static constexpr bool value = std::disjunction_v<std::is_same<TLhs, TRhs>...>;
};

template<typename TLhs, typename TRhs1, typename ...TRhs>
constexpr auto is_one_of_v = is_one_of<TLhs, TRhs1, TRhs...>::value;

} // namespace util
