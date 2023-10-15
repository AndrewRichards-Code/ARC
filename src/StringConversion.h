#pragma once
#include <string>

namespace arc
{
	std::string ToString(const std::wstring& wstring);
	std::wstring ToWString(const std::string& string);
	std::string ToUpper(const std::string& string);
	std::wstring ToUpper(const std::wstring& wstring);
	std::string ToLower(const std::string& string);
	std::wstring ToLower(const std::wstring& wstring);
}