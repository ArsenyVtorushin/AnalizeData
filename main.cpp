#include <Windows.h>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <sstream>

// јнализ данных
// „тение и запись из таблиц
// 


class Name
{
public:
	Name() :Name("", ' ', 0) {}
	Name(std::string name, char sex, int quantity)
		:name(name),
		sex(sex),
		quantity(quantity)
	{}

	Name(const Name& other)
	{
		this->name = other.name;
		this->sex = other.sex;
		this->quantity = other.quantity;
	}

	~Name() = default;


	void SetName(std::string name) { this->name = name; }
	void SetSex(char sex) { this->sex = sex; }
	void SetQuantity(int quantity) { this->quantity = quantity; }

	auto GetName()const -> std::string { return this->name; }
	auto GetSex()const -> char { return this->sex; }
	auto GetQuantity()const -> int { return this->quantity; }


	friend bool operator < (const Name& rsv, const Name& lsv)
	{
		return rsv < lsv;
	}

private:
	std::string name;
	char sex;
	int quantity;
};





int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::vector<Name> data;

	/*
	//===================================================
	// ѕодготовим данные дл€ анализа если их нет
	//
	std::ifstream inf("names.csv");
	if (!inf.is_open())
	{
		inf.open("male_names_rus.txt");
		if (inf.is_open())
		{
			while (!inf.eof())
			{
				std::string tmp;
				std::getline(inf, tmp, '\n');
				data.emplace_back(tmp, 0);
			}
			inf.close();
			{
				// дл€ генерации случайных чисел
				std::mt19937 gen(std::random_device().entropy()); // создали генератор
				std::uniform_int_distribution<int> prov(0, 100'000); // провайдер "причесывает" число в границы
				for (auto& i : data)
				{
					i.SetQuantity(prov(gen));
				}
			}
		}


		//==================================================
		// “естовый вывод
		//
		for (size_t i = 0; i < 10; i++)
		{
			std::cout << data[i].GetName() << " " << data[i].GetQuantity() << '\n';
		}


		//==================================================
		// «аполн€ем names.csv
		// 1-€ строчка это всегда название данных
		// строчки отдел€ютс€ ";"
		// самый универсальный и удобный способ хранени€ данных в виде таблиц
		//
		std::ofstream outf("names.csv");
		outf << "name;quantity;\n";
		for (auto& i : data)
		{
			outf << i.GetName() << ';' << i.GetQuantity() << ";\n";
		}
		outf.close();
	}
	*/

	std::ifstream in_file;
	in_file.open("russian_names.csv");

	if (!in_file.is_open())
	{
		std::cout << "you idiot";
	}
	else
	
	{
		std::string str;
		std::getline(in_file, str, '\n');
		while (!in_file.eof())
		{
			std::string str;
			std::getline(in_file, str, '\n');
			std::stringstream str_stream(str);
			
			std::string name;
			std::string sex;
			std::string quantity;

			std::getline(str_stream, name, ';'); // 1st cell with id doesnt count
			std::getline(str_stream, name, ';');
			std::getline(str_stream, sex, ';');
			std::getline(str_stream, quantity, ';');

			data.emplace_back(name, sex[0], std::stoi(quantity));

			
		}
	}

	in_file.close();

 
	return 0;
}

