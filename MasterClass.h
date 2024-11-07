#pragma once
#include "include.h"


class MasterClass
{
public:
	std::string status; // status = filename
	std::vector<std::string> info; // copy file
	// ���������, �������� �� �� ��� �� ���� 
	bool Reported(std::string data);
	// ��������� ����� ����� � ������ � 
	void Add(std::string data);
	void Add(std::vector<std::string> data);
	// ��������� ������ ������, � ������� �� 
	void Remove_Num(std::string move_to_filename, std::string data);
	void Change_Status(std::string move_to_filename, std::string data);
	void Update();
	std::vector<std::string> Get_Info_Telegram();
	std::vector<std::string> Get_Vector_New_Numbers();
	MasterClass(std::string filename);
};



//				Delete this...
// � ������� ������ ���� ����� ��������� ����������?
/*
class New_Order : public Master_Class
{
public:




	void Get_Info()
	{
		std::cout << this->filename << std::endl;
		print_vec(this->info);
	}

	New_Order(std::string filename) : Master_Class(filename) {}
};
class Deliver_Order : public Master_Class
{

};
class Completed_Order : public Master_Class
{

};
*/