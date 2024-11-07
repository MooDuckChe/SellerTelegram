#pragma once
#include <string>

class Database
{
public:
	void CheckDB(std::string username);
	void CheckDB(unsigned long long user_id);
	void CheckDB();
};

