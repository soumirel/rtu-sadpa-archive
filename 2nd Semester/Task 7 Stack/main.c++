//TODO ���� ����������� �����,
//TODO ��������� ����������� �� �������
//TODO ��������� �������� ���������

#include "stack.c++"

#include <iostream>
#include <locale>

#include <string>

using namespace std;

void printMenu(string& expression);

int calculateExpression(string& expression);

int main()
{
	setlocale(LC_ALL, "ru");

	// ������� ����������
	string expression;

	//���������� ��� ����������������� �����.
	int userMenuChoice = -1;

	// ������� ����-����.
	while (userMenuChoice != 0)
	{
		system("cls");
		printMenu(expression);

		cin >> userMenuChoice;
		cin.ignore();

		switch (userMenuChoice)
		{
		case 1:
			cout << "������� �������������� ��������� � ����������� �������: ";
			cin >> expression;
			system("pause");
			break;

		case 2:
			cout << "�������� ��������� ��������� �����: ";
			cout << calculateExpression(expression);
			cout << endl;
			system("pause");
			break;

		case 0:
			cout << "�� ��������!\n";
			userMenuChoice = 0;
			system("pause");
			break;

		case 2022:
			cout << "���������� :D\n";
			system("pause");
			break;

		default:
			cout << "� �� ������� ���, ��������� ����\n";
			cin.clear();
			system("pause");
			break;
		}
	}

	return 0;
}


void printMenu(string& expression)
{
	cout << "������������ ������ #7 ����-03-21 ������� �.�. ������� 17\n\n"
		"������� 2 - ��������� ��������� � ������ ��������.\n"
		"~~~~~~~~~~~~~~~~~����~~~~~~~~~~~~~~~\n"
		"�������� ���������: ";
	cout << expression << '\n';
	cout << "������� [1], ����� ������ ��������� � ����������� ������� ��� ������.\n"
		"������� [2], ����� �������� �������� ��������� ���������.\n"
		"������� [0], ����� ��������� ������ ���������.\n";
	cout << "��� �����: ";
}


int calculateExpression(string& expression)
{
	Stack <int> operands;
	for (size_t i = 0; i < expression.length(); i++)
	{
		if (expression[i] != '+' &&
			expression[i] != '-' &&
			expression[i] != '*' &&
			expression[i] != '/')
		{
			operands.push(int(expression[i]) - 48);
		}
		else
		{
			int tempResult;
			char op = expression[i];
			int popedFirst = operands.pop();
			int popedLast = operands.pop();
			switch (op)
			{ 
			case '+':
				tempResult = popedLast + popedFirst;
				break;
			case '-':
				tempResult = popedLast - popedFirst;
				break;
			case '/':
				tempResult = popedLast / popedFirst;
				break;
			case '*':
				tempResult = popedLast * popedFirst;
				break;
			}
			operands.push(tempResult);		 
		}
	}
	return operands.pop();
	operands.clear();
}
