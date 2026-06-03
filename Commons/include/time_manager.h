//
// Created by Eniola Olawale on 17/12/2025.
//

#pragma once
#include <chrono>
#include <cstdint>
#include "common_macros.h"
using namespace std::chrono;

namespace commons{
	class COMMON_API TimeManager
	{
	public:
		// Returns current UTC time in seconds since epoch
		static int64_t now_seconds()
		{

			return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
		}

		// Returns current UTC time in milliseconds since epoch
		static int64_t now_milliseconds()
		{
			return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		}

		// Returns current UTC time in microseconds since epoch
		static int64_t now_microseconds()
		{
			return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
		}

		// Returns a formatted string: YYYY-MM-DD HH:MM:SS
		static std::string formatted_utc()
		{
			auto t = system_clock::to_time_t(system_clock::now());
			std::tm tm{};
#if defined(_WIN32)
			gmtime_s(&tm, &t); // Windows safe
#else
			gmtime_r(&t, &tm); // POSIX safe
#endif
			char buf[32];
			std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
			return std::string(buf);
		}
	};

}

