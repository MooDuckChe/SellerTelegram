#pragma once
#include "include.h"

class Settings
{
public:
	static int offset;
	static int limit;
	static int past_time;
	static int future_time;

	static bool offset_set;
	static bool limit_set;
	static bool past_time_set;
	static bool future_time_set;

	static std::string Get_Future_Time();
	static std::string Get_Past_Time();

	static std::string Get_Date_Today();
	static std::string Get_Date_Today(int next_day);
	// ??
	static void Init_Seetings()
	{
		Settings::offset = 0;
		Settings::limit = 100;
		Settings::past_time = 14;
		Settings::future_time = 15;
	}

	static bool Settings_Completed()
	{
		if (offset_set == limit_set == past_time_set == future_time_set == true)
			return true;
		return false;
	}
};

