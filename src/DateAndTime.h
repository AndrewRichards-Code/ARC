#pragma once
#include <string>
#include <chrono>
#include "DebugMacros.h"

namespace arc
{
#if ARC_CXX20
	struct DateAndTimeData
	{
	public:
		DateAndTimeData();
		~DateAndTimeData() = default;

	public:
		std::chrono::year_month_day ymd;
		std::chrono::hh_mm_ss<std::chrono::milliseconds> time;
	};

	std::string GetDateAndTime_LogMessage();
	std::string GetDateAndTime_Filename();
#else
	std::string GetDateAndTime_LogMessage() { return std::string(); }
	std::string GetDateAndTime_Filename() { return std::string(); }
#endif
}