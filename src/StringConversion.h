#pragma once

#include <string>
#include <cwctype>
#include <algorithm>

namespace arc
{
	static std::string ToString(const std::wstring& wstring)
	{
		char* str = new char[wstring.size() + 1];
		wcstombs_s(nullptr, str, wstring.size() + 1, wstring.c_str(), wstring.size() + 1);
		std::string result(str);
		delete[] str;
		return result;
	}

	static std::wstring ToWString(const std::string& string)
	{
		wchar_t* wstr = new wchar_t[string.size() + 1];
		mbstowcs_s(nullptr, wstr, string.size() + 1, string.c_str(), string.size() + 1);
		std::wstring result(wstr);
		delete[] wstr;
		return result;
	}

	static std::string ToUpper(const std::string& string)
	{
		std::string str = string;
		std::transform(str.begin(), str.end(), str.begin(),
			[](unsigned char c) { return std::toupper(c); });
		return str;
	}

	static std::wstring ToUpper(const std::wstring& wstring)
	{
		std::wstring wstr = wstring;
		std::transform(wstr.begin(), wstr.end(), wstr.begin(),
			[](wchar_t c) { return std::towupper(c); });
		return wstr;
	}

	static std::string ToLower(const std::string& string)
	{
		std::string str = string;
		std::transform(str.begin(), str.end(), str.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return str;
	}

	static std::wstring ToLower(const std::wstring& wstring)
	{
		std::wstring wstr = wstring;
		std::transform(wstr.begin(), wstr.end(), wstr.begin(),
			[](wchar_t c) { return std::towlower(c); });
		return wstr;
	}
}