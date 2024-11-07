#include "MasterClass.h"


// Проверяем, сообщали ли мы уже об этом заказе
bool MasterClass::Reported(std::string data)
{
	for (int i = 0; i < this->info.size(); i++)
		if (data == this->info[i])
			return true;

	return false;
}

// Добавляем новый номер в вектор и файл
void MasterClass::Add(std::string data)
{
	info.push_back(data); // Добавляем в вектор 
	File::Write(this->status, data); // Добавляем в файл
}
// Добавляем вектор номеров в вектор и файл
void MasterClass::Add(std::vector<std::string> data)
{
	for (int i = 0; i < data.size(); i++)
	{
		this->info.push_back(data[i]); // Добавляем в вектор 
		File::Write(this->status, data[i]); // Добавляем в файл
	}
}

// Обновляем статус заказа, убираем из файла и вектора
void MasterClass::Remove_Num(std::string move_to_filename, std::string data)
{
	std::erase(info, data); // Удаляем из вектора

	File::Delete_String(this->status, data); // Удаляем из файла
	// add to file another?
	// Send msg telegram
}

// Обновляем статус заказа, убираем из файла и вектора
void MasterClass::Change_Status(std::string move_to_filename, std::string data)
{
	std::erase(info, data); // Удаляем из вектора
	File::Delete_String(this->status, data); // Удаляем из файла

	File::Write(move_to_filename, data);
	//Telegram::Notify(); 
	// add to file another?
	// Send msg telegram
}

void MasterClass::Update()
{

	std::vector<std::string> order_ozon = this->Get_Vector_New_Numbers(); // Получаем текущие заказы c ozon 

	for (int i = 0; i < order_ozon.size(); i++)
	{
		if (!Reported(order_ozon[i]))
		{
			//
			std::string status = Ozon::Get_Status_By_Number(order_ozon[i]);

			if (status == "awaiting_packaging" ||
				status == "awaiting_deliver" ||
				status == "delivering" ||
				status == "cancelled")
			{
				this->Change_Status(status, order_ozon[i]); // Send msg
			}
			else
				std::cout << "Unknow status: " << status << std::endl;
		}
	}
}
std::vector<std::string> MasterClass::Get_Info_Telegram()
{
	// Огрузка на сегодня, завтра и т.д
	// 
	std::vector<std::string> order_ozon = this->Get_Vector_New_Numbers(); // Получаем текущие заказы 


	std::vector<std::string> result;
	std::string test = "[1] Posting_num - Price \
							More ";

	// in all orders
	for (int i = 0; i < order_ozon.size(); i++)
	{
		std::string order = "[" + std::to_string((i + 1)) + "] ";
		nlohmann::json response = Ozon::Get_Info_By_Number(order_ozon[i]);
		// push back name price
		for (int j = 0; j < response["result"]["postings"].size(); j++)
		{
			order += response["result"]["postings"][j]["products"].size();
		}
		// more 


		if (!Reported(order_ozon[i])) // ?
			if (Ozon::Get_Info_By_Status(order_ozon[i]) == this->status)
				result.push_back("New");


		result.push_back(order);
	}
	return result;
}
std::vector<std::string> MasterClass::Get_Vector_New_Numbers()
{
	std::cout << "Break 1\n";
	nlohmann::json request = Ozon::Get_Info_By_Status(this->status);
	std::cout << "Break 2\n";
	try
	{
		size_t size = request["result"]["count"];

		if (size)
		{
			std::vector<std::string> result;
			for (int i = 0; i < size; i++)
				result.push_back(((std::string)request["result"]["postings"][i]["posting_number"]));

			return result;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	return {};
}
MasterClass::MasterClass(std::string filename)
{
	this->status = filename;
	info = File::Read(this->status);

	std::cout << "Init file " << this->status << std::endl;
}