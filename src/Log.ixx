module;
#include <source_location>

export module ARC:Log;
import std.core;
import :EnumClassBitwiseOperators;
import :ConsoleOutputColours;

export namespace arc 
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
		void PrintMessage(Level level, const char* __file__, int __line__, const char* __funcsig__, int64_t errorCode, const std::string_view& format, Args&&... args)
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
		template<typename... Args>
		const std::string GenerateMessage(Level level, const char* __file__, int __line__, const char* __funcsig__, int64_t errorCode, const std::string_view& format, Args&&... args)
		{
			if (level == Level::NONE || (level & m_Level) == Level::NONE)
				return "";

			std::string buffer = std::vformat(format, std::make_format_args(args...));
			
			using namespace std::chrono;
			system_clock::time_point now = system_clock::now();
			time_point day = floor<days>(now);
			year_month_day ymd = year_month_day(day);
			hh_mm_ss<milliseconds> time(duration_cast<milliseconds>(now - day));

			std::stringstream dateTimeSS;
			dateTimeSS << std::setfill('0');
			dateTimeSS << std::setw(4) << std::to_string(ymd.year().operator int());
			dateTimeSS << std::setw(1) << "/";
			dateTimeSS << std::setw(2) << std::to_string(ymd.month().operator unsigned int());
			dateTimeSS << std::setw(1) << "/";
			dateTimeSS << std::setw(2) << std::to_string(ymd.day().operator unsigned int());
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
		Log::Level m_Level = Log::Level::ALL;
		std::string m_LogName;
	};

#if defined(_DEBUG) || defined(ARC_ENABLE_LOGGING)
	
	arc::Log arcDefaultLog;

	struct FormatWithSourceLocation 
	{
		const char* format;
		std::source_location location;

		FormatWithSourceLocation(const char* format, const std::source_location& location = std::source_location::current())
			:format(format), location(location) {}
	};

	template<typename... Args>
	void ARC_FATAL(int64_t errorCode, const FormatWithSourceLocation& format, Args&&... args)
	{
		arcDefaultLog.PrintMessage(arc::Log::Level::FATAL, format.location.file_name(), format.location.line(), format.location.function_name(), errorCode, format.format, std::forward<Args>(args)...);
	}

	template<typename... Args>
	void ARC_ERROR(int64_t errorCode, const FormatWithSourceLocation& format, Args&&... args)
	{
		arcDefaultLog.PrintMessage(arc::Log::Level::ERROR, format.location.file_name(), format.location.line(), format.location.function_name(), errorCode, format.format, std::forward<Args>(args)...);
	}

	template<typename... Args>
	void ARC_WARN(int64_t errorCode, const FormatWithSourceLocation& format, Args&&... args)
	{
		arcDefaultLog.PrintMessage(arc::Log::Level::WARN, format.location.file_name(), format.location.line(), format.location.function_name(), errorCode, format.format, std::forward<Args>(args)...);
	}

	template<typename... Args>
	void ARC_INFO(int64_t errorCode, const FormatWithSourceLocation& format, Args&&... args)
	{
		arcDefaultLog.PrintMessage(arc::Log::Level::INFO, format.location.file_name(), format.location.line(), format.location.function_name(), errorCode, format.format, std::forward<Args>(args)...);
	}

#else

	template<typename... Args>
	void ARC_FATAL(int64_t errorCode, const FormatWithSourceLocation& format, Args&&... args) {}
	
	template<typename... Args>
	void ARC_ERROR(int64_t errorCode, const FormatWithSourceLocation& format, Args&&... args) {}
	
	template<typename... Args>
	void ARC_WARN(int64_t errorCode, const FormatWithSourceLocation& format, Args&&... args) {}
	
	template<typename... Args>
	void ARC_INFO(int64_t errorCode, const FormatWithSourceLocation& format, Args&&... args) {}

#endif

}
