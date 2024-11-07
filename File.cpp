#include "File.h"

// Файл нужен, чтобы если крашнуло программу не уведомлять заново обо всех отгрузках
std::vector<std::string> File::Read(std::string file_name)
{
	std::string filename = "./Files/" + file_name + ".txt";
	std::string line; // Переменная для хранения каждой прочитанной строки


	std::vector<std::string> result;

	std::ifstream file(filename);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			result.push_back(line);
		}
		file.close();
	}
	else
	{
		std::cout << "{The file could not be opened. Create...}\n" << std::endl;
		Write(file_name, "");
	}

	return result;
}
void File::Write(std::string file_name, std::string data)
{
	std::string filename = "./Files/" + file_name + ".txt";
	std::ofstream file(filename, std::ios::app); // Используем флаг std::ios::app, чтобы дописывать данные в конец файла

	if (file.is_open())
	{
		file << data << "\n";
		file.close();

		std::cout << "{Succes write}\n";
	}
	else
		std::cout << "{Error to write.}\n";
}
void File::Clear(std::string file_name)
{
	std::ofstream outFile("./Files/" + file_name + ".txt", std::ofstream::trunc);

	if (outFile.is_open())
	{
		std::cout << "File cleared successfully." << std::endl;
		outFile.close();
	}
	else {
		std::cout << "{The file could not be opened.}" << std::endl;
	}

}
void File::Delete_String(std::string filename, std::string data)
{
	std::vector<std::string> save_file = Read(filename);
	Clear(filename);
	for (int i = 0; i < save_file.size(); i++)
	{
		if (save_file[i] == data)
			continue;
		Write(filename, save_file[i]);
	}
}