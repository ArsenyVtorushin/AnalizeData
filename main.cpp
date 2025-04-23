#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <set>
#include <algorithm>

#define RARE_NAME_UNDER 10000

// Data analisis
// Table reading and writing


//              ������ �����
// ������� ����� ������� �����, ������� ����� �� 
// ����������� � �� ����� ����� �� �����.
// � ������ ����� 10000, �.�. ����������� ���, ��� ������� 
// ���� ����, �� ������� ���


//              ������� �����
// �������� ����� ������� �� �����, �������
// "�� ������", ������� ���� ����� 10000
// � ������� ��� �������, ���� ��� ������� ������ 10000


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


	bool IsRare()const { return this->quantity < RARE_NAME_UNDER; }


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
void MyNameStatistics(const Name name, int max, int min, double average);




int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::multiset<Name> data;

	/*
	//===================================================
	// ���������� ������ ��� ������� ���� �� ���
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
				// ��� ��������� ��������� �����
				std::mt19937 gen(std::random_device().entropy()); // ������� ���������
				std::uniform_int_distribution<int> prov(0, 100'000); // ��������� "�����������" ����� � �������
				for (auto& i : data)
				{
					i.SetQuantity(prov(gen));
				}
			}
		}


		//==================================================
		// �������� �����
		//
		for (size_t i = 0; i < 10; i++)
		{
			std::cout << data[i].GetName() << " " << data[i].GetQuantity() << '\n';
		}


		//==================================================
		// ��������� names.csv
		// 1-� ������� ��� ������ �������� ������
		// ������� ���������� ";"
		// ����� ������������� � ������� ������ �������� ������ � ���� ������
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
	int rareWomen = 0, rareMen = 0;
	int ordinaryWomen = 0, ordinaryMen = 0;

	Name myName;
	int min = names.begin()->GetQuantity();
	double average = 0;

	for (auto& el : names)
	{
		if (el.GetQuantity() > popularAll.GetQuantity())
			popularAll = el;

		if (el.GetSex() == '�')
		{
			if (el.GetQuantity() > popularWomen.GetQuantity())
				popularWomen = el;

			if (el.GetQuantity() == 0)
				zeroWomen++;

			if (el.IsRare())
				rareWomen++;
			else
				ordinaryWomen++;

			frqWomen.push_back(el.GetQuantity());
		}

		if (el.GetSex() == '�')
		{
			if (el.GetQuantity() > popularMen.GetQuantity())
				popularMen = el;

			if (el.GetQuantity() == 0)
				zeroMen++;

			if (el.IsRare())
				rareMen++;
			else
				ordinaryMen++;

			frqMen.push_back(el.GetQuantity());
		}

		frqAll.push_back(el.GetQuantity());

		if (el.GetName() == "�������")
			myName = el;

		average += el.GetQuantity();
	}
	average /= names.size();
	int max = popularAll.GetQuantity();

	std::cout << "1) ����� ���������� ���: " << popularAll.GetName()
		<< "\n     ���-�� ����� ���� �������: " << popularAll.GetQuantity()
		<< "\n     ���-�� ����� ������� ��� ����: " << popularAll.GetQuantity();

	std::cout << "\n\n2) ����� ���������� ��� ����� ������: " << popularWomen.GetName()
		<< "\n   ����� ���������� ��� ����� ������: " << popularMen.GetName();

	std::cout << "\n\n3) �� ����� ���������\n    ����� ����: " << zeroWomen + zeroMen
		<< "\n    ����� ������: " << zeroWomen
		<< "\n    ����� ������: " << zeroMen;

	std::cout << "\n\n4) ��������� �������� �� �������\n    ����� ����: " << Median(frqAll)
		<< "\n    ����� ������: " << Median(frqWomen)
		<< "\n    ����� ������: " << Median(frqMen);

	std::cout << "\n\n5) ������� �������� ��������� ���\n    ����� ����: " << Average(frqAll)
		<< "\n    ����� ������: " << Average(frqWomen)
		<< "\n    ����� ������: " << Average(frqMen);

	std::cout << "\n\n6) ���������� ������ (�� " << RARE_NAME_UNDER << ") ���\n    ����� ���� : " << rareWomen + rareMen
		<< "\n    ����� ������: " << rareWomen
		<< "\n    ����� ������: " << rareMen;

	std::cout << "\n\n6) ���������� ������� (�� " << RARE_NAME_UNDER << ") ���\n    ����� ���� : " << ordinaryWomen + ordinaryMen
		<< "\n    ����� ������: " << ordinaryWomen
		<< "\n    ����� ������: " << ordinaryMen;

	

	MyNameStatistics(myName, max, min, average);
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




void MyNameStatistics(const Name name, int max, int min, double average)
{
	std::cout << "\n\n\n     My Name Statistics\n"
		<< "�� ���: " << name.GetName()
		<< "\n���������� ���������: " << name.GetQuantity();
	if (name.IsRare())
		std::cout << "\n��� ������\n";
	else
		std::cout << "\n��� �������\n";

	std::cout << "�� ������������� �������� ������� ����� ����� ������� ��: " << std::abs(name.GetQuantity() - max)
		<< "\n�� ������������ �������� ������� ����� ����� ������� ��: " << std::abs(name.GetQuantity() - min)
		<< "\n�� �������� �������� ������� ����� ����� ������� ��: " << std::abs(name.GetQuantity() - average) << "\n\n";
}