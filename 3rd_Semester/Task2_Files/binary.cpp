
#include <locale.h>
#include "functionsBin.h"

using namespace std;


void main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	//���������� ��� ����������������� ������.
	int userMenuChoice = -1;

	//���������� ��� ������ ���������
	string textFileName;
	string binFileName;
	bool isTextFileNameEntered = false;
	bool isBinFileNameEntered = false;
	bool isTextFileEmpty = true;

	// ������� ����-����.
	while (userMenuChoice != 10)
	{
		std::system("cls");
		cout << "������������ ������ #2 ����-03-21 ������� �.�. ������� 15\n\n"
			"������� - �����. �������� ������.\n"
			"~~~~~~~~~~~~~~~~~����~~~~~~~~~~~~~~~\n";
		cout << "������� ��� ����������������� ���������� �����: ";
		if (isTextFileNameEntered)
		{
			cout << textFileName << '\n';
		}
		else
		{
			cout << "�� �������\n";
		}
		cout << "������� ��� ����������������� ��������� �����: ";
		if (isBinFileNameEntered)
		{
			cout << binFileName << '\n';
		}
		else
		{
			cout << "�� �������\n";
		}

		cout << "\n������� [0], ����� ������ ��� ���������� �����."
			<< "\n������� [1], ����� ������ ��� ��������� �����."
			<< "\n������� [2], ����� ����������� ������ �� ���������� ����� � ��������."
			<< "\n������� [3], ����� ����������� ������ �� ��������� ����� � ���������."
			<< "\n������� [4], ����� ������� ��� ������ �� ��������� �����."
			<< "\n������� [5], ����� ������� ��� ������ �� ���������� �����."
			<< "\n������� [6], ����� �������� ������ �� ��������� ����� �� � ������."
			<< "\n������� [7], ����� ������� ������ � �������� ����� �� ��������� �����, ���� ������ �� ���������."
			<< "\n������� [8], ����� ������������ � ��������� ����� ������ ������, ���������� � ��������� ������."
			<< "\n������� [9], ����� ������� ���, ����������� � �������� ����."
			<< "\n������� [10], ����� ��������� ������ ���������."
			<< "\n��� �����: ";

		cin >> userMenuChoice;
		cin.ignore();
		if (userMenuChoice == 0 || userMenuChoice == 1)
		{
			switch (userMenuChoice)
			{
			case 0:
			{
				cout << "������� ��� �����:\n";
				cin >> textFileName;
				textFileName += ".txt";
				createTextFile(textFileName);
				isTextFileNameEntered = true;
				break;
			}	

			case 1:
				cout << "������� ��� ��������� �����:\n";
				cin >> binFileName;
				binFileName += ".dat";
				createBinFile(binFileName);
				isBinFileNameEntered = true;
				break;
			}
		}
		else if (isTextFileNameEntered && isBinFileNameEntered)
		{
			if (tryOpenFile(textFileName, 't') && tryOpenFile(binFileName, 'b'))
			{
				switch (userMenuChoice)
				{
				case 2:
					translateTextToBin(textFileName, binFileName);
					cout << "������ �� ���������� ����� ���������� � �������� ����";
					break;

				case 3:
					translateBinToText(textFileName, binFileName);
					break;

				case 4:
					printBinFile(binFileName);
					break;

				case 5:
					printFile�ontents(textFileName);
					break;

				case 6:
				{
					int recordID;
					cout << "������� ����� ������:\n";
					cin >> recordID;
					if (recordID <= countRecordsInBin(binFileName))
					{
						cout << "������ ��� ������� " << recordID <<
							": " << getRecordByID(binFileName, recordID) <<
							'\n';
					}
					else
					{
						cout << "� ����� ������ �������, ��� ��������� �����\n";
					}
					break;
				}
				case 7:
				{
					char recordKey[6];
					cout << "������� ���� ������ (���� � ������� dd.mm)\n";
					cin.getline(recordKey, 6, '\n');

					if (deleteRecordByKey(binFileName, recordKey))
					{
						cout << "������ �� �����: " << recordKey <<
							" �������� �� ��������� ������\n";
					}
					else
					{
						cout << "� ����� ��� ������ � ������: " <<
							recordKey;
					}

					break;
				}

				case 8:
					char month[3];
					cout << "������� ����� � ������� mm:\n";
					cin.get(month, 3);
					copyRecordsByMonth(binFileName, textFileName, month);
					cout << "���������� �������� � ��������� ����\n";
					break;

				case 9:
					cout << "������� ���� � ������� dd.mm:\n";
					char userDate[6];
					cin.getline(userDate, 6, '\n');
					try
					{
						printFriendBirthday(getRecordByKey(binFileName, userDate));
					}
					catch (const std::invalid_argument& invArg) 
					{
						cout << invArg.what() << '\n';
					}
					break;

				case 10:
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
		else
		{
			cout << "��� ����� �� �������!\n";
		}

		std::system("pause");
	}
}