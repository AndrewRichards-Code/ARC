#pragma once

namespace arc
{
	template<typename T>
	bool FindInVector(const std::vector<T>& container, const T& value)
	{
		return std::find(container.begin(), container.end(), value) == container.end();
	}

	template<typename T>
	bool BitwiseCheck(const T& value, const T& checkValue)
	{
		return ((value & checkValue) == checkValue);
	}
}