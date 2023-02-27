#include <iostream>
#include <string>
#include <vector>
#include <ctime>  

#include "City_struct.h"
#include "Timer.h"

using namespace std;

void printMenu(vector<city>& cities);

void printCitiesList(vector<city>& cities);

void generateCitiesList(vector<city>& cities, size_t new_size);

void searchingHub(vector<city>& cities, size_t givenKey);

size_t linearSearch(vector<city>& cities, size_t givenKey);

size_t barierSearch(vector<city>& cities, size_t givenKey);

size_t fibonaccianSearch(vector<city>& cities, size_t givenKey);

vector<city> shellSort(vector<city> cities);




int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(0));

	// ������� ����������
	vector<city> cities;

	//���������� ��� ����������������� ������.
	int userMenuChoice = -1;
	size_t userSize;
	size_t userIndex;

	// ������� ����-����.
	while (userMenuChoice != 0)
	{
		system("cls");
		printMenu(cities);

		cin >> userMenuChoice;
		cin.ignore();

		switch (userMenuChoice)
		{
		case 1:
			cities.clear();
			cout << "������� ������ �������: ";
			cin >> userSize;
			generateCitiesList(cities, userSize);

			system("pause");
			break;
		case 2:

			if (cities.size())
			{
				cout << "������� ����, �� �������� ������ ����� ������ � �������: ";
				cin >> userIndex;
				searchingHub(cities, userIndex);
			}
			else
			{
				cout << "�������� ����������. ��������� �������.\n";
			}

			system("pause");
			break;

		case 0:
			cout << "\n�� ��������!\n";
			userMenuChoice = 0;

			cout << '\n';
			system("pause");
			break;

		case 2022:
			cout << "\n���������� :D\n";

			system("pause");
			break;

		default:
			cout << "\n� �� ������� ���.\n";
			cin.clear();

			cout << '\n';
			system("pause");
			break;
		}
	}

	return 0;
}


void printMenu(vector<city>& cities)
{
	cout << "������������ ������ #9 ����-03-21 ������� �.�. ������� 17\n\n"
		"������� - ��������� ������.\n"
		"~~~~~~~~~~~~~~~~~����~~~~~~~~~~~~~~~\n"
		"�������:\n";
	if (cities.size() <= 10)
	{
		printCitiesList(cities);
	}
	else
	{
		cout << "������������ � �������� � ������.\n������: " 
			<< cities.size() << '\n';
	}

	cout << "\n������� [1], ����� ������������ �������.\n"
		"������� [2], ����� ���������� ����� ��������.\n"
		"������� [0], ����� ��������� ������ ���������.\n";
	cout << "\n��� �����: ";
}

void searchingHub(vector<city>& cities, size_t givenKey)
{
	size_t foundIndex;
	string notFoundString = "������ �� �������.\n";

	cout << "\n����� �������� �� ����� " << givenKey 
		<< " ��� ������ ��������� ���������:\n";
	foundIndex = linearSearch(cities, givenKey);
	if (foundIndex < cities.size())
	{
		cout << "������ ������� � �������� " << foundIndex 
			<< " � ���.���������: " << cities.at(foundIndex).m_name << '\n';
	}
	else
	{
		cout << notFoundString;
	}

	cout << "\n����� �������� �� ����� " << givenKey 
		<< " ��� ������ ���������� ���������:\n";
	foundIndex = barierSearch(cities, givenKey);
	if (foundIndex < cities.size())
	{
		cout << "������ ������� � �������� " << foundIndex 
			<< " � ���.���������: " << cities.at(foundIndex).m_name << '\n';
	}
	else
	{
		cout << notFoundString;
	}

	cout << "\n����� �������� �� ����� " << givenKey
		<< " ��� ������ ��������� ��������:\n"
		<< "(������ �������� ����� ���������� �� ������� �������� ������� ��-�� ����������� ������)\n";
	vector<city> sortedCities = shellSort(cities);

	foundIndex = fibonaccianSearch(sortedCities, givenKey);
	if (foundIndex < cities.size())
	{
		cout << "������ ������� � �������� " << foundIndex 
			<< " � ���.���������: " << sortedCities.at(foundIndex).m_name << '\n';
	}
	else
	{
		cout << notFoundString;
	}
}


void printCitiesList(vector<city>& cities)
{
	size_t size = cities.size();
	
	if (size)
	{
		cout << "��� ������� | �������� ������\n";
		for (size_t i = 0; i < size; i++)
		{
			cout.width(12);
			cout << cities.at(i).m_key;
			cout << "|";
			cout.width(16);
			cout << cities.at(i).m_name;
			cout << endl;
		}
	}
	else
	{
		cout << "�����.\n";
	}
	
}


void generateCitiesList(vector<city>& cities, size_t new_size)
{
	vector<string> cities_names
	{
		"����", "������", "������", "������", "������",
		"������� �����", "������", "���������", "�������",
		"�������", "�������", "������", "���������"
	};

	vector<size_t> codes;
	for (size_t i = 1; i <= new_size; i++)
	{
		codes.push_back(i);
	}

	size_t randomIndex;
	for (size_t i = 0; i < new_size; i++)
	{
		randomIndex = rand() % codes.size();
		cities.push_back(city(codes.at(randomIndex), cities_names.at(rand() % cities_names.size())));
		codes.erase(codes.begin() + randomIndex);
	}
}


// ���������� ����� - ������� ����� �������, ���� ������ ������� � ���.��������� - ������� �������
size_t linearSearch(vector<city>& cities, size_t givenKey)
{
	Timer newTimer;

	for (size_t i = 0; i < cities.size(); i++)
	{
		if (cities.at(i).m_key == givenKey)
		{
			return i;
		}
	}

	return cities.size();
}


// ��������� ����� - ����������� �� �� �����, ��� � ��������
// ������� - ������� ����� �������������� ������� - ���������� �������� ��������
// ��� ����� � ����� ������� ����������� ��������� ������� � ������ ���������, ����� ���������� �����
// ���� ����������� - ���������� �������� ��� ����� ��������.
size_t barierSearch(vector<city>& cities, size_t givenKey)
{
	// ���������� ���������� ��������
	cities.push_back(city(givenKey, ""));

	Timer* newTimer = new Timer();

	size_t i = 0;
	for (; givenKey != cities.at(i).m_key; i++) {}

	delete newTimer;

	cities.erase(cities.end() - 1);

	return i;
}


// ��������-�����. ���� ������ ������� - ���������� ������, �����: ������ ������� + 1
size_t fibonaccianSearch(vector<city>& cities, size_t givenKey)
{
	Timer newTimer;

	// �������������� ����������-������� �������
	size_t size = cities.size();

	// ��������� ������� ����� �������� � ���. m, m-1, m-2
	// ��� m'�� - ����. ����� ��������,������� ���� ������ ������� �������.
	size_t fib_ind_m2 = 0; // m-2'�� ����� ���������.
	size_t fib_ind_m1 = 1; // m-1'�� ����� ���������.
	size_t fib_ind_m = fib_ind_m2 + fib_ind_m1; // m'�� ����� ���������.

	// ����� ������ m'��� ����� ��������, ��� ����.����� ��������, ������� ���� ������ ������� �������.
	while (fib_ind_m < size) 
	{
		fib_ind_m2 = fib_ind_m1;
		fib_ind_m1 = fib_ind_m;
		fib_ind_m = fib_ind_m2 + fib_ind_m1;
	}

	// �������������� ������� - ������������.
	int offset = -1;

	// ���� �� ������� � �������, �.� ���� �������� ����� � ���������� ����� ��������.
	while (fib_ind_m > 1) 
	{
		// �������� �� ��, ����� m-2'�� ����� �������� ��������� �� �������
		size_t i = min(offset + fib_ind_m2, size - 1);

		// ���� � ������, ��� �������� �� ������� fib_ind_m2,
		// ������������� ����� ������� � ���������: offset �� i
		if (cities.at(i).m_key < givenKey)
		{
			fib_ind_m = fib_ind_m1;
			fib_ind_m1 = fib_ind_m2;
			fib_ind_m2 = fib_ind_m - fib_ind_m1;
			offset = i;
		}

		// ���� � ������, ��� �������� �� ������� fib_ind_m2,
		// ������������� ����� �������, ������������� � ������� i + 1
		else if (cities.at(i).m_key > givenKey)
		{
			fib_ind_m = fib_ind_m2;
			fib_ind_m1 = fib_ind_m1 - fib_ind_m2;
			fib_ind_m2 = fib_ind_m - fib_ind_m1;
		}

		// ������� �������� �������, ������� ������� i
		else
			return i;
	}

	// �������� ���������� �������� � �������.
	if (fib_ind_m1 && cities.at(offset + 1).m_key == givenKey)
		return offset + 1;

	// ������� �������� �� �������, ������� ������� �������
	return cities.size() + 1;
}


vector<city> shellSort(vector<city> cities)
{
	size_t size = cities.size();
	for (size_t d = size / 2; d > 0; d /= 2)
	{
		for (size_t i = d; i < size; ++i)
		{
			for (int j = i - d; j >= 0 && cities.at(j).m_key > cities.at(j + d).m_key; j -= d)
			{
				std::swap(cities.at(j), cities.at(j + d));
			}
		}
	}
	return cities;
}