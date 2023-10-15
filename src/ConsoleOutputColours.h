#pragma once
#include <string>

namespace arc
{
	enum class FormatAtrributes : uint32_t
	{
		Default = 0,
		Bold = 1,
		Dim = 2,
		Italics = 3,
		Underlined = 4,
		Blink = 5,
		Reverse = 7,
		Hidden = 8
	};

	enum class ForegroundColour : uint32_t
	{
		Default = 39,
		Black = 30,
		Red = 31,
		Green = 32,
		Yellow = 33,
		Blue = 34,
		Magenta = 35,
		Cyan = 36,
		Light_Gray = 37,
		Dark_Gray = 90,
		Light_Red = 91,
		Light_Green = 92,
		Light_Yellow = 93,
		Light_Blue = 94,
		Light_Magenta = 95,
		Light_Cyan = 96,
		White = 97
	};

	enum class BackgroundColour : uint32_t
	{
		Default = 49,
		Black = 40,
		Red = 41,
		Green = 42,
		Yellow = 43,
		Blue = 44,
		Magenta = 45,
		Cyan = 46,
		Light_Gray = 47,
		Dark_Gray = 100,
		Light_Red = 101,
		Light_Green = 102,
		Light_Yellow = 103,
		Light_Blue = 104,
		Light_Magenta = 105,
		Light_Cyan = 106,
		White = 107
	};

	enum class ResetFormatAttributes : uint32_t
	{
		All = 0,
		Bold = 21,
		Dim = 22,
		Underlined = 24,
		Blink = 25,
		Reverse = 27,
		Hidden = 28
	};

	void PrintColourFormatString(const std::string& str,
		ForegroundColour fColour = ForegroundColour::Default,
		FormatAtrributes format = FormatAtrributes::Default,
		BackgroundColour bColour = BackgroundColour::Default,
		ResetFormatAttributes reset = ResetFormatAttributes::All);
}