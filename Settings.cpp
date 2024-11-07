#include "Settings.h"


int Settings::future_time = 15;
bool Settings::future_time_set = true;

int Settings::past_time = 15;
bool Settings::past_time_set = true;

int Settings::limit = 100;
bool Settings::limit_set = true;

int Settings::offset = 0;
bool Settings::offset_set = true;

std::string Settings::Get_Future_Time()
{
	// Дата 2 недели вперед
	auto future = std::chrono::system_clock::now() + std::chrono::days(Settings::future_time);
	time_t t_future = std::chrono::system_clock::to_time_t(future);
	struct tm* ptm_future = gmtime(&t_future);
	char future_str[21];
	strftime(future_str, sizeof(future_str), "%Y-%m-%dT00:00:00Z", ptm_future);

	return future_str;
}
std::string Settings::Get_Past_Time()
{
	// Дата 2 недели назад
	auto past = std::chrono::system_clock::now() - std::chrono::days(Settings::past_time); // Поменять 
	time_t t_past = std::chrono::system_clock::to_time_t(past);
	struct tm* ptm_past = gmtime(&t_past);
	char past_str[21];
	strftime(past_str, sizeof(past_str), "%Y-%m-%dT00:00:00Z", ptm_past);

	return past_str;
}

std::string Settings::Get_Date_Today()
{
	auto past = std::chrono::system_clock::now(); // Поменять 
	time_t t_past = std::chrono::system_clock::to_time_t(past);
	struct tm* ptm_past = gmtime(&t_past);
	char past_str[21];
	strftime(past_str, sizeof(past_str), "%Y-%m-%d", ptm_past);

	return past_str;
}

std::string Settings::Get_Date_Today(int next_day)
{
	auto past = std::chrono::system_clock::now() + std::chrono::days(next_day); // Поменять 
	time_t t_past = std::chrono::system_clock::to_time_t(past);
	struct tm* ptm_past = gmtime(&t_past);
	char past_str[21];
	strftime(past_str, sizeof(past_str), "%Y-%m-%d", ptm_past);

	return past_str;
}