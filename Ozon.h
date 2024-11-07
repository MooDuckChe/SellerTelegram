#pragma once
#include "include.h"

class Ozon
{
public:
	static nlohmann::json POST_Request(std::string url, nlohmann::json body);
	static nlohmann::json Make_Body_Order(std::string date_from, std::string date_to, bool sort, std::string status);
	static nlohmann::json Get_Info_By_Status(std::string status);
	static nlohmann::json Get_Info_By_Number(std::string order_num);
	static std::string    Get_Status_By_Number(std::string order_num);
	static nlohmann::json Make_Ready_to_Deliver(std::string posting_num);
};
