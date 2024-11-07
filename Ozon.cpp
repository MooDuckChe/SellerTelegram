#include "Ozon.h"


nlohmann::json Ozon::POST_Request(std::string url, nlohmann::json body)
{
	SetConsoleOutputCP(CP_UTF8);

	cpr::Response r = cpr::Post
	(
		cpr::Url{ url },
		cpr::Body{ body.dump() },
		cpr::Header
		{
			{ "Client-Id", Api::Client_Id},
			{ "Api-Key",   Api::Api_Key}
		}
	);


	if (r.status_code == 200)
	{
		nlohmann::json j = nlohmann::json::parse(r.text);
		std::cout << "Code response: " << r.status_code << std::endl;
		std::cout << "Response: " << std::setw(4) << j << std::endl;
	}
	else
		std::cout << r.status_code << "\n" << r.text << std::endl;

	// —разу вернуть распарсенный json
	return nlohmann::json::parse(r.text);
}
nlohmann::json Ozon::Make_Body_Order(std::string date_from, std::string date_to, bool sort, std::string status)
{
	// 2024-01-01T00:00:01Z
	// sorting ? ASC : DESC;
	// Global set? /revers
	// asc Ч по возрастанию,
	// desc Ч по убыванию.
	// std::string
	// ‘ормат: YYYY-MM-DDThh:mm:ssZ. ѕример: 2020-01-31T08:30:59Z.
	nlohmann::json json_obj =
	{
		{"dir", sort ? "DESC" : "ASC"},
		{"filter",
			{
				{"cutoff_from", Settings::Get_Past_Time()},
				{"cutoff_to",   Settings::Get_Future_Time()},
				{"delivery_method_id", nlohmann::json::array()},
				{"provider_id", nlohmann::json::array()},
				{"status", status},
				{"warehouse_id", nlohmann::json::array()}
			}
		},
		{"limit", 100},
		{"offset", 0},
		{"with",
			{
				{"analytics_data", false},
				{"barcodes", false},
				{"financial_data", false},
				{"translit", false}
			}
		}
	};
	return json_obj;
}
nlohmann::json Ozon::Get_Info_By_Status(std::string status)
{
	std::cout << status << std::endl;
	nlohmann::json info = POST_Request("https://api-seller.ozon.ru/v3/posting/fbs/unfulfilled/list", Make_Body_Order("", "", false, status));
	return info;
}
nlohmann::json Ozon::Get_Info_By_Number(std::string posting_num)
{
	// Log

	std::cout << "get_info\n";
	nlohmann::json json_body =
	{
		{"posting_number", posting_num},
		{"with",
			{
				{"analytics_data", false},
				{"barcodes", false},
				{"financial_data", false},
				{"translit", false}
			}
		}
	};

	return POST_Request("https://api-seller.ozon.ru/v3/posting/fbs/get", json_body);
}
std::string    Ozon::Get_Status_By_Number(std::string posting_num)
{
	nlohmann::json json_body =
	{
		{"posting_number", posting_num},
		{"with",
			{
				{"analytics_data", false},
				{"barcodes", false},
				{"financial_data", false},
				{"translit", false}
			}
		}
	};
	try
	{
		return POST_Request("https://api-seller.ozon.ru/v3/posting/fbs/get", json_body)["result"]["status"];
	}
	catch (const std::exception& e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}
	return "Empty";
}
nlohmann::json Ozon::Make_Ready_to_Deliver(std::string posting_num)
{
	nlohmann::json info = Ozon::Get_Info_By_Number(posting_num);

	nlohmann::json ReturnedJsonData = {
		{"packages", {}},
		{"posting_number", posting_num}
	};


	for (int i = 0; i < info["result"]["products"].size(); i++) {
		ReturnedJsonData["packages"][0]["products"].push_back
		(
			{
				{"product_id", info["result"]["products"][i]["sku"]},
				{ "quantity", info["result"]["products"][i]["quantity"]}
			}
		);
	}

	return ReturnedJsonData;
}