#pragma once
#include <vector>
#include "EnumClassBitwiseOperators.h"

namespace arc
{
	template<typename T>
	bool FindInVector(const std::vector<T>& container, const T& value)
	{
		return std::find(container.begin(), container.end(), value) != container.end();
	}

	template<typename T>
	typename std::vector<T>::const_iterator FindPositionInVectorConst(const std::vector<T>& container, const T& value)
	{
		return std::find(container.cbegin(), container.cend(), value);
	}

	template<typename T>
	typename std::vector<T>::iterator FindPositionInVector(std::vector<T>& container, const T& value)
	{
		return std::find(container.begin(), container.end(), value);
	}

	template<typename T>
	bool BitwiseCheck(const T& value, const T& checkValue)
	{
		return ((value & checkValue) == checkValue);
	}

	template<typename T>
	typename T Align(T value, T alignment)
	{
		return (value + (alignment - 1)) & ~(alignment - 1);
	};
}