#pragma once

#include <vector>

namespace util
{
	template <typename T>
	std::vector<T>& vectorize(std::vector<T>& vec)
	{
		return vec;
	}

	template <typename TFirst, typename... TArgs>
	std::vector<TFirst>& vectorize(std::vector<TFirst>& vec, const TFirst& first, const TArgs& ... args)
	{
		vec.push_back(first);

		return vectorize(vec, args...);
	}

	template <typename TFirst, typename... TArgs>
	std::vector<TFirst> vectorize(const TFirst& first, const TArgs& ... args)
	{
		std::vector<TFirst> vec;

		vec.reserve((sizeof... (args)) + 1);

		return vectorize(vec, first, args...);
	}
} // namespace  util
