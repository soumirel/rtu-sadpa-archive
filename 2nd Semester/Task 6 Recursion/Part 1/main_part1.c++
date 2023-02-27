#include <iostream>
#include <string>
#include <windows.h>
#include <locale>
#include <cmath>

#include "BracketsBalance.h"

using namespace std;


void printMenu(string& inputedString);

void printString(string& inputedString);

void inputString(string& inputedString);

void balanceCheckerHub(string inputedString);

BracketsBalance checkBrcaketsBalance(string str, BracketsBalance balance, size_t ind = 0);



void main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// ������� ����������
	string inputedString;

	//���������� ��� ����������������� �����.
	int userMenuChoice = -1;

	// ������� ����-����.
	while (userMenuChoice != 0) 
	{
		system("cls");
		printMenu(inputedString);

		cin >> userMenuChoice;
		cin.ignore();

		switch (userMenuChoice) 
		{
		case 1:
			inputString(inputedString);
			system("pause");
			break;

		case 2:
			if (inputedString.size() > 0)
			{
				balanceCheckerHub(inputedString);
			}
			else
			{
				cout << "�������� ����������. ������� ������.\n";
			}
			system("pause");
			break;

		case 0:
			cout << "�� ��������!\n";
			userMenuChoice = 0;
			system("pause");
			break;

		default:
			cout << "� �� ������� ���, ��������� ����\n";
			cin.clear();
			system("pause");
			break;
		}
	}
}


void printString(string& inputedString)
{
	if (inputedString.length() != 0)
	{
		cout << inputedString << endl;
	}
	else
	{
		cout << "�� �������\n";
	}
}


void printMenu(string& inputedString)
{
	cout << "������������ ������ #6 ����-03-21 ������� �.�. ������� 17\n\n"
		"������� 6 - ����������� ���������.\n"
		"~~~~~~~~~~~~~~~~~����~~~~~~~~~~~~~~~\n"
		"�������� ������: ";
	printString(inputedString);
	cout << "������� [1], ����� ������ ������.\n"
		"������� [2], ����� ������ ������ ������.\n"
		"������� [0], ����� ��������� ������ ���������.\n";
	cout << "��� �����: ";
}


void inputString(string& inputedString)
{
	cout << "������� ������, ����� ������� ������� [Enter]: ";
	getline(cin, inputedString);
}


void balanceCheckerHub(string inputedString)
{
	BracketsBalance balance;
	balance = checkBrcaketsBalance(inputedString, balance);

	if (balance.roundBalance == 0)
	{
		cout << "�����c ������� ������ �������\n";
	}
	else
	{
		cout << "� ������ �� ������� " << abs(balance.roundBalance) <<
			(balance.roundBalance < 0 ? " ����������� " : " ����������� ") <<
			"������� ������\n";
	}

	if (balance.squareBalance == 0)
	{
		cout << "�����c ���������� ������ �������\n";
	}
	else 
	{
		cout << "� ������ �� ������� " << abs(balance.squareBalance) <<
			(balance.squareBalance < 0 ? " ����������� " : " ����������� ") <<
			"���������� ������\n";
	}

	if (balance.bracesBalance == 0)
	{
		cout << "�����c �������� ������ �������\n";
	}
	else
	{
		cout << "� ������ �� ������� " << abs(balance.bracesBalance) <<
			(balance.bracesBalance < 0 ? " ����������� " : " ����������� ") <<
			"�������� ������\n";
	}
}


BracketsBalance checkBrcaketsBalance(string str, BracketsBalance balance, size_t ind)
{
	while (ind < str.size())
	{
		switch (str[ind])
		{
		case '(':
			balance.roundBalance++;
			break;
		case ')':
			balance.roundBalance--;
			break;
		case '[':
			balance.squareBalance++;
			break;
		case ']':
			balance.squareBalance--;
			break;
		case '{':
			balance.bracesBalance++;
			break;
		case '}':
			balance.bracesBalance--;
			break;
		}
		return checkBrcaketsBalance(str, balance, ind + 1);
	}
	return (balance);
}