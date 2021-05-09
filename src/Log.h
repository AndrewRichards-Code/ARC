#pragma once

#include <string>
#include <iomanip>
#include <sstream>
#include "../dep/DATE/date.h"

#include "ConsoleOutputColours.h"
#include "EnumClassBitwiseOperators.h"

#ifdef ERROR //Found in wingdi.h
#undef ERROR
#endif

namespace arc 
{
	class Log
	{
		//Function Pointers
	private:
		typedef std::string (*PFN_ErrorCodeToString)(uint64_t errorCode);
		inline static PFN_ErrorCodeToString ErrorCodeToString;

		//enums/structs
	public:
		enum class Level : uint8_t
		{
			NONE	= 0x00,
			FATAL	= 0x01,
			ERROR	= 0x02,
			WARN	= 0x04,
			INFO	= 0x08,
			ALL		= 0xFF,
		};

		//Methods
	public:
		template<typename... Args>
		static void PrintMessage(Level level, const char* __file__, int __line__, const char* __funcsig__, uint64_t errorCode, const char* format, Args&&... args)
		{
			std::string msg = GenerateMessage(level, __file__, __line__, __funcsig__, errorCode, format, std::forward<Args>(args)...);

			if (!msg.empty())
			{
				ForegroundColour fColour = ForegroundColour::Default;
				FormatAtrributes format = FormatAtrributes::Default;
				GetConsoleOutputColour(level, fColour, format);
				PrintColourFormatString(msg, fColour, format);
			}
		}

	private:
		static const std::string GenerateMessage(Level level, const char* __file__, int __line__, const char* __funcsig__, uint64_t errorCode, const char* format, ...)
		{
			if (level == Level::NONE || (level & s_Level) == Level::NONE)
				return "";

			std::string buffer(BufferSize, 0);
			va_list args;
			va_start(args, format);
			vsprintf_s(&buffer[0], BufferSize, format, args);
			va_end(args);

			std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
			auto day = date::floor<date::days>(now);
			auto ymd = date::year_month_day(day);
			auto time = date::make_time(std::chrono::duration_cast<std::chrono::milliseconds>(now - day));
			std::stringstream dateTimeSS;
			dateTimeSS << std::setfill('0');
			dateTimeSS << std::setw(4) << std::to_string(int(ymd.year()));
			dateTimeSS << std::setw(1) << "/";
			dateTimeSS << std::setw(2) << std::to_string(unsigned(ymd.month()));
			dateTimeSS << std::setw(1) << "/";
			dateTimeSS << std::setw(2) << std::to_string(unsigned(ymd.day()));
			dateTimeSS << std::setw(1) << " ";
			dateTimeSS << std::setw(2) << std::to_string(time.hours().count());
			dateTimeSS << std::setw(1) << ":";
			dateTimeSS << std::setw(2) << std::to_string(time.minutes().count());
			dateTimeSS << std::setw(1) << ":";
			dateTimeSS << std::setw(2) << std::to_string(time.seconds().count());
			dateTimeSS << std::setw(1) << ".";
			dateTimeSS << std::setw(3) << std::to_string(time.subseconds().count());
			dateTimeSS << " UTC";

			std::stringstream resultSS; 
			resultSS << "[" << dateTimeSS.str() << "][" << LogLevelToString(level) << ": " << __file__ << "(" << std::to_string(__line__) << "): " << __funcsig__ << "][ErrorCode: " << (ErrorCodeToString ? ErrorCodeToString(errorCode) : std::to_string(errorCode)) << "]: " << buffer;

			return resultSS.str();
		}
	public:
		static void SetLevel(Level level = Level::NONE)
		{
			s_Level = level;
		}

		static void SetErrorCodeToString(PFN_ErrorCodeToString pfn)
		{
			ErrorCodeToString = pfn;
		}

	private:
		static const std::string LogLevelToString(Level level) noexcept
		{
			switch (level)
			{
			default:
			case Log::Level::NONE:
				return "NONE";
			case Log::Level::FATAL:
				return "FATAL";
			case Log::Level::ERROR:
				return "ERROR";
			case Log::Level::WARN:
				return "WARN";
			case Log::Level::INFO:
				return "INFO";
			case Log::Level::ALL:
				return "ALL";
			};
		}

		static void GetConsoleOutputColour(Level level, ForegroundColour& fColour, FormatAtrributes& format)
		{
			format = FormatAtrributes::Default;

			switch (level)
			{
			default:
			case Log::Level::NONE:
				fColour = ForegroundColour::Default; return;
			case Log::Level::FATAL:
				fColour = ForegroundColour::Red; format = FormatAtrributes::Bold; return;
			case Log::Level::ERROR:
				fColour = ForegroundColour::Red; return;
			case Log::Level::WARN:
				fColour = ForegroundColour::Yellow; return;
			case Log::Level::INFO:
				fColour = ForegroundColour::Green; return;
			case Log::Level::ALL:
				fColour = ForegroundColour::Default; return;
			};
		}

	//Member
	private:
		constexpr inline static size_t BufferSize = 1024Ui64;
		inline static Log::Level s_Level = Log::Level::ALL;
	};
}

#if defined(_DEBUG) || defined(ARC_ENABLE_LOGGONG)

#define ARC_FATAL(errorCode, fmt, ...) arc::Log::PrintMessage(arc::Log::Level::FATAL, __FILE__, __LINE__, ARC_FUNCSIG, errorCode, fmt, __VA_ARGS__);
#define ARC_ERROR(errorCode, fmt, ...) arc::Log::PrintMessage(arc::Log::Level::ERROR, __FILE__, __LINE__, ARC_FUNCSIG, errorCode, fmt, __VA_ARGS__);
#define ARC_WARN(errorCode, fmt, ...) arc::Log::PrintMessage(arc::Log::Level::WARN, __FILE__, __LINE__, ARC_FUNCSIG, errorCode, fmt, __VA_ARGS__);
#define ARC_INFO(errorCode, fmt, ...) arc::Log::PrintMessage(arc::Log::Level::INFO, __FILE__, __LINE__, ARC_FUNCSIG, errorCode, fmt, __VA_ARGS__);

#else

#define ARC_FATAL(errorCode, fmt, ...)
#define ARC_ERROR(errorCode, fmt, ...)
#define ARC_WARN(errorCode, fmt, ...)
#define ARC_INFO(errorCode, fmt, ...)

#endif
