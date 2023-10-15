#include "ConsoleOutputColours.h"

#if defined(_MSC_VER)
#pragma warning(disable : 4100) //Disables 'Unreferenced formal parameter' warning C4100
#include <iostream>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

#elif defined(__ANDROID__)
#include <iostream>
#include <android/log.h>

#elif defined(__linux__)
#include <iostream>

#endif

namespace arc
{
	void PrintColourFormatString(const std::string& str, 
		ForegroundColour fColour, 
		FormatAtrributes format, 
		BackgroundColour bColour, 
		ResetFormatAttributes reset)
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
		std::cout << str << std::endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED));

#elif defined(__linux__) && ! defined(__ANDROID__)
		std::string output;
		output += "\033[";
		output += std::to_string(static_cast<uint32_t>(format)) + std::string(";");
		output += std::to_string(static_cast<uint32_t>(fColour)) + std::string(";");
		output += std::to_string(static_cast<uint32_t>(bColour)) + std::string("m");
		output += str;
		output += "\033[";
		output += std::to_string(static_cast<uint32_t>(reset)) + std::string("m");
		std::cout << output << std::endl;

#elif defined(__ANDROID__)
		__android_log_write(ANDROID_LOG_INFO, "", str.c_str());
		std::cout << str << std::endl;

#else
		std::cout << str << std::endl;
#endif
	}
}