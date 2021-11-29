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
		typedef std::string (*PFN_ErrorCodeToString)(int64_t errorCode);
		PFN_ErrorCodeToString pfnErrorCodeToString;

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
		Log(const std::string& logName = "ARC")
			:m_LogName(logName) {}
		~Log() = default;

		template<typename... Args>
		void PrintMessage(Level level, const char* __file__, int __line__, const char* __funcsig__, int64_t errorCode, const char* format, Args&&... args)
		{
			std::string msg = GenerateMessage(level, __file__, __line__, __funcsig__, errorCode, format, std::forward<Args>(args)...);

			if (!msg.empty())
			{
				ForegroundColour fColour = ForegroundColour::Default;
				FormatAtrributes fAtrrib = FormatAtrributes::Default;
				GetConsoleOutputColour(level, fColour, fAtrrib);
				PrintColourFormatString(msg, fColour, fAtrrib);
			}
		}
		
		void SetLevel(Level level = Level::NONE)
		{
			m_Level = level;
		}
		void SetErrorCodeToStringFunction(PFN_ErrorCodeToString pfn)
		{
			pfnErrorCodeToString = pfn;
		}

	private:
		const std::string GenerateMessage(Level level, const char* __file__, int __line__, const char* __funcsig__, int64_t errorCode, const char* format, ...)
		{
			if (level == Level::NONE || (level & m_Level) == Level::NONE)
				return "";

			std::string buffer(m_BufferSize, 0);
			va_list args;
			va_start(args, format);
		#if defined(_MSC_VER)
			vsprintf_s(buffer.data(), m_BufferSize, format, args);
		#else
			vsnprintf(buffer.data(), m_BufferSize, format, args);
		#endif
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
			resultSS << "[" << dateTimeSS.str() << "][" << m_LogName << ": " << LogLevelToString(level) << ": " << __file__ << "(" << std::to_string(__line__) << "): " << __funcsig__ << "][ErrorCode: " << (pfnErrorCodeToString ? pfnErrorCodeToString(errorCode) : std::to_string(errorCode)) << "]: " << buffer;

			return resultSS.str();
		}
	
	private:
		const std::string LogLevelToString(Level level) noexcept
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
		void GetConsoleOutputColour(Level level, ForegroundColour& fColour, FormatAtrributes& format)
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
		const size_t m_BufferSize = 1024;
		Log::Level m_Level = Log::Level::ALL;
		std::string m_LogName;
	};
}

#if defined(_DEBUG) || defined(ARC_ENABLE_LOGGONG)
static arc::Log arcDefaultLog;
#define ARC_LOG_INSTANCE arcDefaultLog

#define ARC_FATAL(errorCode, fmt, ...) ARC_LOG_INSTANCE.PrintMessage(arc::Log::Level::FATAL, __FILE__, __LINE__, ARC_FUNCSIG, errorCode, fmt, __VA_ARGS__)
#define ARC_ERROR(errorCode, fmt, ...) ARC_LOG_INSTANCE.PrintMessage(arc::Log::Level::ERROR, __FILE__, __LINE__, ARC_FUNCSIG, errorCode, fmt, __VA_ARGS__)
#define ARC_WARN(errorCode, fmt, ...) ARC_LOG_INSTANCE.PrintMessage(arc::Log::Level::WARN, __FILE__, __LINE__, ARC_FUNCSIG, errorCode, fmt, __VA_ARGS__)
#define ARC_INFO(errorCode, fmt, ...) ARC_LOG_INSTANCE.PrintMessage(arc::Log::Level::INFO, __FILE__, __LINE__, ARC_FUNCSIG, errorCode, fmt, __VA_ARGS__)

#else

#define ARC_FATAL(errorCode, fmt, ...)
#define ARC_ERROR(errorCode, fmt, ...)
#define ARC_WARN(errorCode, fmt, ...)
#define ARC_INFO(errorCode, fmt, ...)

#endif
