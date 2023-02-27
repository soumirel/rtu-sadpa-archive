
#include <locale.h>
#include "functionsText.h"

using namespace std;


void main()
{
	setlocale(LC_ALL, "ru");

	//���������� ��� ����������������� ������.
	int userMenuChoice = -1;

	//���������� ��� ������ ���������
	string fileName;
	bool isNameEntered = false;

	// ������� ����-����.
	while (userMenuChoice != 7)
	{
		std::system("cls");
		cout << "������������ ������ #2 ����-03-21 ������� �.�. ������� 15\n\n"
			"������� - �����.\n"
			"~~~~~~~~~~~~~~~~~����~~~~~~~~~~~~~~~\n";
		cout << "������� ��� �����: ";
		if (isNameEntered)
		{
			cout << fileName << '\n';
		}
		else
		{
			cout << "�� �������\n";
		}

		cout	<< "\n������� [0], ����� ������ ��� �����."
			<< "\n������� [1], ����� ������� ���� � �������."
			<< "\n������� [2], ����� ������� ���������� �����."
			<< "\n������� [3], ����� �������� ����� ������ � ����� �����."
			<< "\n������� [4], ����� ������� ����� �� ����� �� ��� ������."
			<< "\n������� [5], ����� ������ ���������� ����� � �����."
			<< "\n������� [6], ����� c������ ����� ���� �� �������� ���������,"
			<< "\n             �������� ��� �� ������� �������������� "
			<< "\n             ���� ������������� �������������� �����."
			<< "\n������� [7], ����� ��������� ������ ���������."
			<< "\n��� �����: ";
		cin >> userMenuChoice;
		cin.ignore();
		if (userMenuChoice == 0)
		{
			cout << "������� ��� �����:\n";
			cin >> fileName;
			fileName += ".txt";
			isNameEntered = true;
		}
		if (isNameEntered)
		{
			if (userMenuChoice == 1)
			{
				if (isFileExist(fileName) == true)
				{
					cout << "���� � ����� ������ ��� ���������!\n";
				}
				else
				{
					createFile(fileName);
				}
			}
			else if (userMenuChoice >= 2 && userMenuChoice <= 7)
			{
				if (tryOpenFile(fileName))
				{
					switch (userMenuChoice)
					{
					case 2:
						printFile�ontents(fileName);
						break;

					case 3:
						addNewString(fileName);
						break;

					case 4:
						int numberID;
						cout << "������� ����� �����:\n";
						cin >> numberID;
						if (numberID <= countAmountOfNumbers(fileName))
						{
							cout << "����� ��� ������� " << numberID <<
								": " << getNumberByID(fileName, numberID) <<
								'\n';
						}
						else
						{
							cout << "� ����� ������ �����, ��� ��������� �����\n";
						}
						break;

					case 5:
						cout << "���������� ����� � �����: " << countAmountOfNumbers(fileName) << '\n';
						break;

					case 6:
					{
						string newFileName;
						cout << "������� ��� ������ �����:\n";
						cin >> newFileName;
						if (isFileExist(newFileName) == true)
						{
							cout << "���� � ����� ������ ��� ���������!\n";
						}
						else
						{
							newFileName += ".txt";
							specialTask(fileName, newFileName);
						}
						break;
					}

					case 7:
						cout << "\n�� ��������!\n";
						break;

					default:
						cout << "\n� �� ������� ���.\n";
						cin.clear();
						break;
					}
				}
				else
				{
					cout << "������ �������� �����\n";
				}
			}
		}
		else
		{
			cout << "��� ����� �� �������!\n";
		}
		
		std::system("pause");
	}
}