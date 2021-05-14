#pragma once

#include "DebugMacros.h"
#include <string>

#if defined(_MSC_VER)
#pragma warning(disable : 4100) //Disables 'Unreferenced formal parameter' warning C4100

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#endif

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

	static void PrintColourFormatString(const std::string& str, 
		ForegroundColour fColour = ForegroundColour::Default, 
		FormatAtrributes format = FormatAtrributes::Default, 
		BackgroundColour bColour = BackgroundColour::Default, 
		ResetFormatAttributes reset = ResetFormatAttributes::All)
	{
#if defined(_WIN64)
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		WORD dwFColour = 0;

		switch (fColour)
		{
		case arc::ForegroundColour::Default:
			dwFColour = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED; break;
		case arc::ForegroundColour::Black:
			dwFColour = 0; break;
		case arc::ForegroundColour::Red:
			dwFColour = FOREGROUND_RED; break;
		case arc::ForegroundColour::Green:
			dwFColour = FOREGROUND_GREEN; break;
		case arc::ForegroundColour::Yellow:
			dwFColour = FOREGROUND_GREEN | FOREGROUND_RED; break;
		case arc::ForegroundColour::Blue:
			dwFColour = FOREGROUND_BLUE; break;
		case arc::ForegroundColour::Magenta:
			dwFColour = FOREGROUND_BLUE | FOREGROUND_RED; break;
		case arc::ForegroundColour::Cyan:
			dwFColour = FOREGROUND_BLUE | FOREGROUND_GREEN; break;
		case arc::ForegroundColour::Light_Gray:
			dwFColour = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED; break;
		case arc::ForegroundColour::Dark_Gray:
			dwFColour = FOREGROUND_INTENSITY;  break;
		case arc::ForegroundColour::Light_Red:
			dwFColour = FOREGROUND_RED | FOREGROUND_INTENSITY; break;
		case arc::ForegroundColour::Light_Green:
			dwFColour = FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
		case arc::ForegroundColour::Light_Yellow:
			dwFColour = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY; break;
		case arc::ForegroundColour::Light_Blue:
			dwFColour = FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
		case arc::ForegroundColour::Light_Magenta:
			dwFColour = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY; break;
		case arc::ForegroundColour::Light_Cyan:
			dwFColour = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
		case arc::ForegroundColour::White:
			dwFColour = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY; break;
		default:
			break;
		}

		WORD dwBColour = 0;
		switch (bColour)
		{
		case arc::BackgroundColour::Default:
			dwBColour = 0; break;
		case arc::BackgroundColour::Black:
			dwBColour = 0; break;
		case arc::BackgroundColour::Red:
			dwBColour = BACKGROUND_RED; break;
		case arc::BackgroundColour::Green:
			dwBColour = BACKGROUND_GREEN; break;
		case arc::BackgroundColour::Yellow:
			dwBColour = BACKGROUND_GREEN | BACKGROUND_RED; break;
		case arc::BackgroundColour::Blue:
			dwBColour = BACKGROUND_BLUE; break;
		case arc::BackgroundColour::Magenta:
			dwBColour = BACKGROUND_BLUE | BACKGROUND_RED; break;
		case arc::BackgroundColour::Cyan:
			dwBColour = BACKGROUND_BLUE | BACKGROUND_GREEN; break;
		case arc::BackgroundColour::Light_Gray:
			dwBColour = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED; break;
		case arc::BackgroundColour::Dark_Gray:
			dwBColour = BACKGROUND_INTENSITY;  break;
		case arc::BackgroundColour::Light_Red:
			dwBColour = BACKGROUND_RED | BACKGROUND_INTENSITY; break;
		case arc::BackgroundColour::Light_Green:
			dwBColour = BACKGROUND_GREEN | BACKGROUND_INTENSITY; break;
		case arc::BackgroundColour::Light_Yellow:
			dwBColour = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY; break;
		case arc::BackgroundColour::Light_Blue:
			dwBColour = BACKGROUND_BLUE | BACKGROUND_INTENSITY; break;
		case arc::BackgroundColour::Light_Magenta:
			dwBColour = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY; break;
		case arc::BackgroundColour::Light_Cyan:
			dwBColour = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY; break;
		case arc::BackgroundColour::White:
			dwBColour = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY; break;
		default:
			break;
		}

		SetConsoleTextAttribute(hConsole, (dwFColour + dwBColour));
		ARC_PRINTF("%s\n", str.c_str());
		SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED));

#elif defined(__linux__)
		std::string output;
		output += "\033[";
		output += std::to_string(static_cast<uint32_t>(format)) + std::string(";");
		output += std::to_string(static_cast<uint32_t>(fColour)) + std::string(";");
		output += std::to_string(static_cast<uint32_t>(bColour)) + std::string("m");
		output += str;
		output += "\033[";
		output += std::to_string(static_cast<uint32_t>(reset)) + std::string("m");
		ARC_PRINTF("%s\n", output.c_str());
#else
		ARC_PRINTF("%s\n", str.c_str());
#endif
	}
}