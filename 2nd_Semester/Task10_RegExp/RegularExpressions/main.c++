#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

void printMenu();
void checkText();

int main()
{
	setlocale(LC_ALL, "Russian");

	// ������� ����������
	string userString = "";

	//���������� ��� ����������������� ������.
	int userMenuChoice = -1;

	// ������� ����-����.
	while (userMenuChoice != 0)
	{
		system("cls");
		printMenu();

		cin >> userMenuChoice;
		cin.ignore();

		switch (userMenuChoice)
		{
		case 1:
			checkText();
			system("pause");
			break;

		case 0:
			cout << "\n�� ��������!\n";
			userMenuChoice = 0;

			cout << '\n';
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

void printMenu()
{
	cout << "������������ ������ #10 ����-03-21 ������� �.�. ������� 17\n\n"
		"������� - ���������� ���������.\n"
		"~~~~~~~~~~~~~~~~~����~~~~~~~~~~~~~~~\n";

	cout << "\n������� [1], ����� ��������� ��������� ����� � �����\n"
		"������� [0], ����� ��������� ������ ���������.\n";
	cout << "\n��� �����: ";
}

void checkText()
{
	string userPhrase = "";

	cout << "������� �����, ������� ������ ����������� � ������:";
	getline(cin, userPhrase);

	regex regular(userPhrase);

	cout << "������� [1], ����� ������ ����������� ����� � ����������.\n"
		"������� [2], ����� ��������� �����, ������������ � ����� \"Text.txt\"\n";
	int userChecktypeChose;
	cin >> userChecktypeChose;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	
	bool isContains = false;
	switch (userChecktypeChose)
	{
	case 1:
	{
		string textForCheck = "";
		cout << "������� ����� ��� ��������: ";
		getline(cin, textForCheck);

		regex_iterator<string::iterator> iterator(textForCheck.begin(), textForCheck.end(), regular);
		
		for (regex_iterator<string::iterator> end; iterator != end; iterator++)
		{
			if (iterator->str().empty() == false)
			{
				isContains = true;
				break;
			}
		}
		break;
	}

	case 2:
	{
		std::ifstream file("Text.txt");
		std::string buffer;

		while (!file.eof())
		{
			file >> buffer;
			regex_iterator<string::iterator> iterator(buffer.begin(), buffer.end(), regular);

			for (regex_iterator<string::iterator> end; iterator != end; iterator++)
			{
				if (iterator->str().empty() == false)
				{
					isContains = true;
					break;
				}
			}
		}

		file.close();
		break;
	}
	default:
		cout << "����������� ����!\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		break;
	}

	if (isContains)
	{
		cout << "� ������ ";
	}
	else
	{
		cout << "� ������ �� ";
	}
	cout << "���������� ����� \"" << userPhrase << "\"\n";
}