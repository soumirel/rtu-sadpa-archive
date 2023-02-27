
#include <locale.h>
#include "Hash.h"
#include "Binary.h"
#include "HashBinary.h"
#include "Test.h"

using namespace std;

enum MenuState
{
	INIT = 0,
	PRINT_FILE = 1,
	PRINT_TABLE = 2,
	INSERT = 3,
	GET = 4,
	DELETE = 5,
	START_TEST = 6,
	EXIT = 7
};

void main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	//���������� ��� ����������������� ������.
	int userMenuChoice = -1;

	//���������� ��� ������ ���������
	HashTable* table = nullptr;
	string binFileName;
	int recordsAmount = 0;
	bool isDataInit = false;

	// ������� ����-����.
	while (userMenuChoice != EXIT)
	{
		std::system("cls");
		cout << "������������ ������ #3 ����-03-21 ������� �.�. ������� 15\n\n"
			"������� - ���-�������.\n"
			"~~~~~~~~~~~~~~~~~����~~~~~~~~~~~~~~~\n";

		cout << "������� [0], ����� ����������������� �������������� ������:"
			"\n\t������ ��� ����� � ������������� ���"
			"\n\t���������������� ���-������� � �������� ������.\n"
			"\n������� [1], ����� ������� ���������� ��������� �����."
			"\n������� [2], ����� ������� ���������� ���-�������."
			"\n������� [3], ����� �������� ������� � �������."
			"\n������� [4], ����� �������� �������� �� �����."
			"\n������� [5], ����� ������� �������� �� �����."
			"\n������� [6], ����� ��������� ������������."
			"\n������� [7], ����� ��������� ������ ���������."
			"\n��� �����: ";
		cin >> userMenuChoice;
		if (!isDataInit && userMenuChoice > 0
			&& userMenuChoice != EXIT
			&& userMenuChoice != START_TEST)
		{
			cout << "������� ���������������� �������������� ������!\n";
		}
		else
		{
			cin.ignore();
			switch (userMenuChoice)
			{
			case INIT:
				cout << "������� ��� ��������� �����: ";
				cin >> binFileName;
				binFileName += ".dat";

				int generatingRecordsAmount;
				cout << "������� ���������� ������������ �������: ";
				cin >> generatingRecordsAmount;
				generateBinFile(binFileName, generatingRecordsAmount);
				recordsAmount = generatingRecordsAmount;

				if (table != nullptr)
				{
					delete table;
				}
				table = new HashTable();
				synchronizeTableWithFile(binFileName, table);

				if (!isDataInit) isDataInit = true;

				break;

			case PRINT_FILE:
				printBinFile(binFileName);
				break;

			case PRINT_TABLE:
				table->printTable();
				break;

			case INSERT:
			{
				cout << "������� ���� (���� ��������) � ������� dd.mm: ";
				char key_date[6];
				cin.getline(key_date, 6, '\n');
				cout << "������� ��� (���� �.) ����������� � ��� ����: ";
				char name[6];
				cin.getline(name, 8, '\n');
				table->add(key_date, name, ++recordsAmount);
				addRecord(binFileName, key_date, name, recordsAmount);
				break;
			}

			case GET:
			{
				char key_date[6];
				cout << "������� ���� (���� � ������� dd.mm) �� �������� ������ ������: ";
				cin.getline(key_date, 6, '\n');
				char name[8];
				cout << "�� �����: " << key_date << ' ';
				try
				{
					cout << "������� �������� " << getRecord(binFileName, table, key_date) << '\n';
				}
				catch (const std::invalid_argument& invArg)
				{
					cout << invArg.what() << '\n';
				}
				break;
			}

			case DELETE:
				char key_date[6];
				cout << "������� ���� (���� � ������� dd.mm) �� �������� ������� ������: ";
				cin.getline(key_date, 6, '\n');
				deleteRecordByKeyInBoth(binFileName, table, key_date);
				break;

			case START_TEST:
				try
				{
					testHeshT();
				}
				catch (const std::exception& exeption)
				{
					cout << exeption.what() << '\n';
				}
				
				break;

			case EXIT:
				cout << "\n�� ��������!\n";
				break;

			default:
				cout << "\n� �� ������� ���.\n";
				cin.clear();
				break;
			}
		}

		std::system("pause");
	}
}