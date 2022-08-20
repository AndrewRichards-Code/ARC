#pragma once
#include <string>
#include <sstream>
#include <chrono>

namespace arc
{
	struct DateAndTimeData
	{
	public:
		DateAndTimeData()
		{
			std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
			const std::chrono::time_zone* timeZone = std::chrono::current_zone();

			std::chrono::time_point nowLocal = timeZone->to_local(now);
			std::chrono::time_point day = floor<std::chrono::days>(nowLocal);

			ymd = std::chrono::year_month_day(day);
			time = std::chrono::hh_mm_ss<std::chrono::milliseconds>(duration_cast<std::chrono::milliseconds>(nowLocal - day));
		}
		~DateAndTimeData() = default;

	public:
		std::chrono::year_month_day ymd;
		std::chrono::hh_mm_ss<std::chrono::milliseconds> time;
	};

	static std::string GetDateAndTime_LogMessage()
	{
		DateAndTimeData dateAndTimeData;
		auto ymd = dateAndTimeData.ymd;
		auto time = dateAndTimeData.time;

		std::stringstream dateTime;
		dateTime << std::setfill('0');
		dateTime << std::setw(4) << std::to_string(ymd.year().operator int());
		dateTime << std::setw(1) << "/";
		dateTime << std::setw(2) << std::to_string(ymd.month().operator unsigned int());
		dateTime << std::setw(1) << "/";
		dateTime << std::setw(2) << std::to_string(ymd.day().operator unsigned int());
		dateTime << std::setw(1) << " ";
		dateTime << std::setw(2) << std::to_string(time.hours().count());
		dateTime << std::setw(1) << ":";
		dateTime << std::setw(2) << std::to_string(time.minutes().count());
		dateTime << std::setw(1) << ":";
		dateTime << std::setw(2) << std::to_string(time.seconds().count());
		dateTime << std::setw(1) << ".";
		dateTime << std::setw(3) << std::to_string(time.subseconds().count());

		return dateTime.str();
	}

	static std::string GetDateAndTime_Filename()
	{
		DateAndTimeData dateAndTimeData;
		auto ymd = dateAndTimeData.ymd;
		auto time = dateAndTimeData.time;

		std::stringstream dateTime;
		dateTime << std::setfill('0');
		dateTime << std::setw(4) << std::to_string(ymd.year().operator int());
		dateTime << std::setw(2) << std::to_string(ymd.month().operator unsigned int());
		dateTime << std::setw(2) << std::to_string(ymd.day().operator unsigned int());
		dateTime << std::setw(1) << "_";
		dateTime << std::setw(2) << std::to_string(time.hours().count());
		dateTime << std::setw(2) << std::to_string(time.minutes().count());

		return dateTime.str();
	}
}