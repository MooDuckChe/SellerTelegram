#pragma once
#include "include.h"

class File
{
public:
	static std::vector<std::string> Read(std::string file_name);
	static void Write(std::string file_name, std::string data);
	static void Clear(std::string file_name);
	static void Delete_String(std::string filename, std::string data);
};