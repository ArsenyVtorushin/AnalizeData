#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <set>
#include <algorithm>


// Data analisis
// Table reading and writing


//              Редкие имена
// Редкими можно назвать имена, которые почти не 
// встречаются и их почти никто не носит.
// Я выбрал число 10000, т.к. большинство имён, чья частота 
// ниже него, не знакомы мне



class Name
{
public:
	Name() :Name("", ' ', 0) {} // default constructor - for vector/list storage
	Name(std::string name, char sex, int quantity)
		:name(name),
		sex(sex),
		quantity(quantity)
	{}

	Name(const Name& other) // copy constructor - for vector/list storage
	{
		this->name = other.name;
		this->sex = other.sex;
		this->quantity = other.quantity;
	}

	~Name() = default; // public destructor - for vector/list storage


	void SetName(std::string name) { this->name = name; }
	void SetSex(char sex) { this->sex = sex; }
	void SetQuantity(int quantity) { this->quantity = quantity; }

	auto GetName()const -> std::string { return this->name; }
	auto GetSex()const -> char { return this->sex; }
	auto GetQuantity()const -> int { return this->quantity; }


	friend bool operator < (const Name& rsv, const Name& lsv)
	{
		for (size_t i = 0; i < (rsv.GetName().size() < lsv.GetName().size() ? rsv.GetName().size() : lsv.GetName().size())/* min name size */; i++)
		{
			if (rsv.GetName()[i] < lsv.GetName()[i])
			{
				return true;
			}
			else if (rsv.GetName()[i] > lsv.GetName()[i])
			{
				return false;
			}
		}
		return false;
	}

private:
	std::string name; // set/multiset comparison field
	char sex;
	int quantity;
};





void Statistics(std::multiset<Name> names);
double Median(std::vector<int> frqs);
double Average(std::vector<int> frqs);




int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::multiset<Name> data;

	/*
	//===================================================
	// Подготовим данные для анализа если их нет
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
				// для генерации случайных чисел
				std::mt19937 gen(std::random_device().entropy()); // создали генератор
				std::uniform_int_distribution<int> prov(0, 100'000); // провайдер "причесывает" число в границы
				for (auto& i : data)
				{
					i.SetQuantity(prov(gen));
				}
			}
		}


		//==================================================
		// Тестовый вывод
		//
		for (size_t i = 0; i < 10; i++)
		{
			std::cout << data[i].GetName() << " " << data[i].GetQuantity() << '\n';
		}


		//==================================================
		// Заполняем names.csv
		// 1-я строчка это всегда название данных
		// строчки отделяются ";"
		// самый универсальный и удобный способ хранения данных в виде таблиц
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
		std::getline(in_file, str, '\n'); // first string is heading, we skip it
		while (!in_file.eof())
		{
			std::string str;
			std::getline(in_file, str, '\n');
			std::stringstream str_stream(str);
			
			std::string name;
			std::string sex;
			std::string quantity;

			std::getline(str_stream, name, ';'); // first cell with id doesn't count
			std::getline(str_stream, name, ';');
			std::getline(str_stream, sex, ';');
			std::getline(str_stream, quantity, ';');

			data.insert({ name, sex[0], std::stoi(quantity) });
		}
	}

	in_file.close();

	Statistics(data);

	return 0;
}





void Statistics(std::multiset<Name> names)
{
	Name popularAll{ *names.begin() };
	Name popularWomen{ *names.begin() };
	Name popularMen{ *names.begin() };

	std::vector<int> frqAll;
	std::vector<int> frqMen;
	std::vector<int> frqWomen;

	int zeroWomen = 0, zeroMen = 0;


	for (auto& el : names)
	{
		if (el.GetQuantity() > popularAll.GetQuantity())
			popularAll = el;

		if (el.GetSex() == 'Ж')
		{
			if (el.GetQuantity() > popularWomen.GetQuantity())
				popularWomen = el;

			if (el.GetQuantity() == 0)
				zeroWomen++;

			frqWomen.push_back(el.GetQuantity());
		}

		if (el.GetSex() == 'М')
		{
			if (el.GetQuantity() > popularMen.GetQuantity())
				popularMen = el;

			if (el.GetQuantity() == 0)
				zeroMen++;

			frqMen.push_back(el.GetQuantity());
		}

		frqAll.push_back(el.GetQuantity());
	}

	std::cout << "1) Самое популярное имя: " << popularAll.GetName()
		<< "\n     Кол-во среди всех записей: " << popularAll.GetQuantity()
		<< "\n     Кол-во среди записей его пола: " << popularAll.GetQuantity();

	std::cout << "\n\n2) Самое популярное имя среди женщин: " << popularWomen.GetName()
		<< "\n   Самое популярное имя среди мужчин: " << popularMen.GetName();

	std::cout << "\n\n3) Не имеют носителей\n    Среди всех: " << zeroWomen + zeroMen
		<< "\n    Среди женщин: " << zeroWomen
		<< "\n    Среди мужчин: " << zeroMen;

	std::cout << "\n\n4) Медианное значение по частоте\n    Среди всех: " << Median(frqAll)
		<< "\n    Среди женщин: " << Median(frqWomen)
		<< "\n    Среди мужчин: " << Median(frqMen);

	std::cout << "\n\n5) Среднее значение носителей имён\n    Среди всех: " << Average(frqAll)
		<< "\n    Среди женщин: " << Average(frqWomen)
		<< "\n    Среди мужчин: " << Average(frqMen);
}




double Median(std::vector<int> frqs)
{
	std::sort(frqs.begin(), frqs.end());

	if (frqs.size() % 2 != 0)
		return frqs[frqs.size() / 2];
	else
		return (frqs[frqs.size() / 2 - 1] + frqs[frqs.size() / 2]) / 2;
}



double Average(std::vector<int> frqs)
{
	int sum = 0;
	for (auto& el : frqs)
		sum += el;
	return sum / frqs.size();
}
