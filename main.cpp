#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>

// ������ ������
// ������ � ������ �� ������
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
	::setlocale(LC_ALL, "ru"); // :: - ���������� ��� ���������� ���������� ����������� ������� ����� ��

	std::vector<NameQuantity> data; 

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
					i.quantity = prov(gen);
				}
			}
		}


		//==================================================
		// �������� �����
		//
		for (size_t i = 0; i < 10; i++)
		{
			std::cout << data[i].name << " " << data[i].quantity << '\n';
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
			outf << i.name << ';' << i.quantity << ";\n";
		}
		outf.close();
	}
 
	return 0;
}