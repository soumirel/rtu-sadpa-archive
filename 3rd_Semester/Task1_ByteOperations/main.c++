#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int operation_1(size_t number);
int operation_2(size_t number);
int operation_3(size_t number);
int operation_4(size_t number);
int operation_5(size_t number, size_t position);
void printBinaryNumberOnBorders(size_t number, size_t width);


int main()
{
	setlocale(LC_ALL, "ru");

	//���������� ��� ����������������� ������.
	int userMenuChoice = -1;

	//���������� ��� ������ ���������
	size_t number = 0;
	bool isNumberInit = false;

	// ������� ����-����.
	while (userMenuChoice != 6)
	{
		system("cls");
		cout << "������������ ������ #1 ����-03-21 ������� �.�. ������� 16\n\n"
			"������� - ������� ��������.\n"
			"~~~~~~~~~~~~~~~~~����~~~~~~~~~~~~~~~\n"
			"����� � hex �������: ";
		if (isNumberInit)
		{
			cout << hex << uppercase << number << '\n';
		}
		else
		{
			cout << "�� �������\n";
		}

		cout << "\n������� [0], ����� ������ ����� � hex �������."
			<< "\n������� [1], ����� ���������� 1, 2 � 7 ������� � 1."
			<< "\n������� [2], ����� �������� 7-9 �������."
			<< "\n������� [3], ����� �������� ����� �� 8 (� 10��)."
			<< "\n������� [4], ����� ��������� ����� �� 8 (� 10��)."
			<< "\n������� [5], ����� �������� n-�� ���, ��������� ����� (����������������� �������� � ��.�������)."
			<< "\n������� [6], ����� ��������� ������ ���������."
			<< "\n��� �����: ";

		cin >> userMenuChoice;
		cin.ignore();
		if (userMenuChoice > 0 && userMenuChoice < 6)
		{
			if (isNumberInit)
			{
				size_t position = 0;
				if (userMenuChoice == 5)
				{
					cout << "������� ����� �������, ������� ������ ��������: ";
					cin >> position;
				}
				size_t result = 0;
				switch (userMenuChoice)
				{
				case 1:
					result = operation_1(number);
					break;
				case 2:
					result = operation_2(number);
					break;
				case 3:
					result = operation_3(number);
					break;
				case 4:
					result = operation_4(number);					
					break;
				case 5:
					result = operation_5(number, position);					
					break;
				}
				size_t numberWidth;
				if (number == 0 && result == 0)
				{
					numberWidth = 1;
				}
				else
				{
					numberWidth = max(log2(number) + 1, log2(result) + 1);
				}
				
				cout << setw(25) << "�������� ����� � 2��: ";
				printBinaryNumberOnBorders(number, numberWidth);
				cout << setw(25) << "��������� ��������: ";
				printBinaryNumberOnBorders(result, numberWidth);
				system("pause");
			}
			else
			{
				cout << "�������� ����������. ������� �����.\n";
				system("pause");
			}
		}
		else
		{
			switch (userMenuChoice)
			{
			case 0:
				cout << "������� ����� � hex �������: ";
				cin.unsetf(ios::dec);
				cin.setf(ios::hex);
				cin >> number;
				isNumberInit = true;
				system("pause");
				break;
			case 6:
				cout << "\n�� ��������!\n";

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
	}

	return 0;
}



int operation_1(size_t number)
{
	size_t mask = 0b10000110;
	cout << "�����: ";
	printBinaryNumberOnBorders(mask, log2(mask) + 1);
	return number | mask;
}


int operation_2(size_t number)
{
	size_t mask = 0b1110000000;
	cout << "�����: ";
	printBinaryNumberOnBorders(mask, log2(mask) + 1);
	return number & ~mask;
}


int operation_3(size_t number)
{
	return number << 3;
}


int operation_4(size_t number)
{
	return number >> 3;
}


int operation_5(size_t number, size_t position)
{
	size_t mask = 0b1;
	cout << "�����: ";
	printBinaryNumberOnBorders(mask, log2(mask) + 1);
	return number & ~(mask << position);
}


void printBinaryNumberOnBorders(size_t number, size_t width)
{
	string result = "";
	int zeros;
	if (number != 0)
	{
		int ownWidth = (log2(number) + 1);
		zeros = width - ownWidth;
	}
	else
	{
		zeros = width;
	}
	
	while (number > 0)
	{
		result = to_string(number % 2) + result;
		number /= 2;
	}
	for (int i = 0; i < zeros; i++)
	{
		cout << '0';
	}
	cout << result << '\n';
}