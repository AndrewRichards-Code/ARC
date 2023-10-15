#pragma once
#include "ConsoleOutputColours.h"
#include "EnumClassBitwiseOperators.h"
#include "DebugMacros.h"

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
			None	= 0x00,
			Fatal	= 0x01,
			Error	= 0x02,
			Warn	= 0x04,
			Info	= 0x08,
			All		= 0xFF,
		};

		//Methods
	public:
		Log(const std::string& logName = "ARC");
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
		
		void SetLevel(Level level = Level::None);
		void SetErrorCodeToStringFunction(PFN_ErrorCodeToString pfn);

	private:
		const std::string GenerateMessage(Level level, const char* __file__, int __line__, const char* __funcsig__, int64_t errorCode, const char* format, ...);
	
	private:
		const std::string LogLevelToString(Level level) noexcept;
		void GetConsoleOutputColour(Level level, ForegroundColour& fColour, FormatAtrributes& format);

	//Member
	private:
		Log::Level m_Level = Log::Level::All;
		std::string m_LogName;
	};
}

#if defined(_DEBUG) || defined(ARC_ENABLE_LOGGONG)
static arc::Log arcDefaultLog;
#define ARC_LOG_INSTANCE arcDefaultLog

#define ARC_FATAL(errorCode, fmt, ...) ARC_LOG_INSTANCE.PrintMessage(arc::Log::Level::Fatal, __FILE__, __LINE__, ARC_FUNCSIG, errorCode, fmt, __VA_ARGS__)
#define ARC_ERROR(errorCode, fmt, ...) ARC_LOG_INSTANCE.PrintMessage(arc::Log::Level::Error, __FILE__, __LINE__, ARC_FUNCSIG, errorCode, fmt, __VA_ARGS__)
#define ARC_WARN(errorCode, fmt, ...) ARC_LOG_INSTANCE.PrintMessage(arc::Log::Level::Warn, __FILE__, __LINE__, ARC_FUNCSIG, errorCode, fmt, __VA_ARGS__)
#define ARC_INFO(errorCode, fmt, ...) ARC_LOG_INSTANCE.PrintMessage(arc::Log::Level::Info, __FILE__, __LINE__, ARC_FUNCSIG, errorCode, fmt, __VA_ARGS__)

#else

#define ARC_FATAL(errorCode, fmt, ...)
#define ARC_ERROR(errorCode, fmt, ...)
#define ARC_WARN(errorCode, fmt, ...)
#define ARC_INFO(errorCode, fmt, ...)

#endif
