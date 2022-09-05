#pragma once

#include "ConsoleOutputColours.h"
#include "DateAndTime.h"
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

			va_list args;
			va_start(args, format);
		#if defined(_MSC_VER)
			size_t bufferSize = static_cast<size_t>(_vscprintf(format, args)) + 1;
			char* bufferData = new char[bufferSize];
			vsprintf_s(bufferData, bufferSize, format, args);
		#else
			va_list args2;
			va_copy(args2, args);
			size_t bufferSize = static_cast<size_t>(vsnprintf(nullptr, 0, format, args2)) + 1;
			va_end(args2);
			char* bufferData = new char[bufferSize];
			vsnprintf(bufferData, bufferSize, format, args);
		#endif
			va_end(args);
			std::string buffer = bufferData;
			delete[] bufferData;

			const std::string& dateTime = GetDateAndTime_LogMessage();

			std::stringstream resultSS; 
			resultSS << "[" << dateTime << "][" << m_LogName << ": " << LogLevelToString(level) << ": " << __file__ << "(" << std::to_string(__line__) << "): " << __funcsig__ << "][ErrorCode: " << (pfnErrorCodeToString ? pfnErrorCodeToString(errorCode) : std::to_string(errorCode)) << "]: " << buffer;

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
				return "WARNING";
			case Log::Level::INFO:
				return "INFORMATION";
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
