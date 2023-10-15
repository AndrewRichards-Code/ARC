#include "Log.h"
#include "DateAndTime.h"
#include <stdarg.h>

using namespace arc;

Log::Log(const std::string& logName)
	:m_LogName(logName) {}

void Log::SetLevel(Level level)
{
	m_Level = level;
}

void Log::SetErrorCodeToStringFunction(PFN_ErrorCodeToString pfn)
{
	pfnErrorCodeToString = pfn;
}

const std::string Log::GenerateMessage(Level level, const char* __file__, int __line__, const char* __funcsig__, int64_t errorCode, const char* format, ...)
{
	if (level == Level::None || (level & m_Level) == Level::None)
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

const std::string Log::LogLevelToString(Level level) noexcept
{
	switch (level)
	{
	default:
	case Log::Level::None:
		return "NONE";
	case Log::Level::Fatal:
		return "FATAL";
	case Log::Level::Error:
		return "ERROR";
	case Log::Level::Warn:
		return "WARNING";
	case Log::Level::Info:
		return "INFORMATION";
	case Log::Level::All:
		return "ALL";
	};
}

void Log::GetConsoleOutputColour(Level level, ForegroundColour& fColour, FormatAtrributes& format)
{
	format = FormatAtrributes::Default;

	switch (level)
	{
	default:
	case Log::Level::None:
		fColour = ForegroundColour::Default; return;
	case Log::Level::Fatal:
		fColour = ForegroundColour::Red; format = FormatAtrributes::Bold; return;
	case Log::Level::Error:
		fColour = ForegroundColour::Red; return;
	case Log::Level::Warn:
		fColour = ForegroundColour::Yellow; return;
	case Log::Level::Info:
		fColour = ForegroundColour::Green; return;
	case Log::Level::All:
		fColour = ForegroundColour::Default; return;
	};
}
