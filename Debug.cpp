#include "Debug.h"

namespace Debug
{
	void print_vec(std::vector<std::string> data)
	{
		for (int i = 0; i < data.size(); i++)
		{
			std::cout << data[i] << std::endl;
		}
	}
	void Call_All_Status()
	{
		std::vector<std::string> req = {
			"awaiting_registration",
			"acceptance_in_progress",
			"awaiting_approve",
			"awaiting_packaging",
			"awaiting_deliver",
			"arbitration",
			"client_arbitration",
			"delivering",
			"driver_pickup",
			"cancelled",
			"not_accepted",
			"sent_by_seller"
		};

		for (int i = 0; i < req.size(); i++)
		{
			std::cout << req[i] << std::endl;
			//Ozon::POST_Request("https://api-seller.ozon.ru/v3/posting/fbs/unfulfilled/list", Ozon::Get_Body_Order("", "", false, req[i]));
		}
	}
}


//
//
//
//std::vector<std::string> Save_Info(nlohmann::json request)
//{
//	
//	// Date
//	// send_id
//	// count + name + price
//	// price_all
//
//	system("chcp 1251 > nul");
//	std::vector<std::string> response;
//
//	// Date
//	response.push_back("Дата отгрузки:");
//	std::string date = request["result"]["postings"][0]["shipment_date"];
//	response.push_back(date.erase(date.length() - 10, 10));
//
//	// Number order
//	response.push_back("Номер отправления:");
//	response.push_back(request["result"]["postings"][0]["posting_number"]);
//
//	// Count + name
//	response.push_back("Наименование проданного товара:");
//	//response.push_back(/*request["result"]["postings"][0]["products"][0]["quantity"] +*/ " шт - " + request["result"]["postings"][0]["products"][0]["name"]);
//
//	//int fuck_me = request["result"]["postings"][0]["products"][0]["quantity"];
//	//std::cout << fuck_me << std::endl;
//	//std::string fuck_nmee = request["result"]["postings"][0]["products"][0]["quantity"];
//	//std::cout << fuck_nmee << std::endl;
//	//
//	response.push_back(std::to_string(((int)request["result"]["postings"][0]["products"][0]["quantity"])));
//	response.push_back(" шт - ");
//	response.push_back((std::string)request["result"]["postings"][0]["products"][0]["name"]);
//	
//	// Price
//	response.push_back("\nЦена проданного товара:");
//	response.push_back(request["result"]["postings"][0]["products"][0]["price"]);
//
//
//
//	return response;
//}

