#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>

// јнализ данных
// „тение и запись из таблиц
// 
// 
//


struct NameQuantity
{
	std::string name; 
	int quantity;

	NameQuantity() :NameQuantity("", 0) {}

	NameQuantity(std::string name, int quantity)
		:name(name),
		quantity(quantity)
	{}
};





int main()
{
	::setlocale(LC_ALL, "ru"); // :: - обознчение дл€ глобальной библиотеки стандартных функций €зыка —и

	std::vector<NameQuantity> data; 

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
					i.quantity = prov(gen);
				}
			}
		}


		//==================================================
		// “естовый вывод
		//
		for (size_t i = 0; i < 10; i++)
		{
			std::cout << data[i].name << " " << data[i].quantity << '\n';
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
			outf << i.name << ';' << i.quantity << ";\n";
		}
		outf.close();
	}
 
	return 0;
}