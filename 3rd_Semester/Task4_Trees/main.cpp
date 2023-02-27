
#include <locale.h>
#include "Tree.h"
#include "TreePrinter.h"
#include "TreeFunctions.h"

using namespace std;

bool checkCorrectExpression(string expression);

enum MenuState
{
	DEFAULT = -1,
	INIT = 0,
	PRINT = 1,
	SUBTREES = 2,
	CALCULATE_TREE = 3,
	EXIT = 4
};

void main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	//���������� ��� ����������������� ������.
	int userMenuChoice = -1;
	Tree* tree = nullptr;
	TreePrinter* printer = new TreePrinter();

	//���������� ��� ������ ���������
	bool isExpressionEntered = false;
	string expression = "";

	// ������� ����-����.
	while (userMenuChoice != EXIT)
	{
		std::system("cls");
		cout << "������������ ������ #4 ����-03-21 ������� �.�. ������� 15\n\n"
			"������� - �������.\n"
			"~~~~~~~~~~~~~~~~~����~~~~~~~~~~~~~~~\n";
		
		if (isExpressionEntered) cout << "������� ���������: " << expression << '\n';
		else cout << "��������� �� ������.\n";
		
		cout << "������� [0], ����� ������ ����� ���������."
			"\n������� [1], ����� ������� ������ ���������."
			"\n������� [2], ����� ��������� �������� �����������."
			"\n������� [3], ����� ��������� �������� ������ ���� ���������� ������ � ������� ����������."
			"\n������� [4], ����� ��������� ������ ���������."
			"\n��� �����: ";

		cin >> userMenuChoice;
		cin.ignore();

		if (userMenuChoice < INIT || userMenuChoice > EXIT)
		{
			cout << "������! ������������ ����.";
			userMenuChoice = DEFAULT;
		}

		if (userMenuChoice != DEFAULT && userMenuChoice != INIT && !isExpressionEntered)
		{
			cout << "������! ��������� �� ������.";
			userMenuChoice = DEFAULT;
		}
		else 
		{
			switch (userMenuChoice)
			{
				case INIT:
				{
					cout << "������� ���������\n"
						"��� ���������: <�������>::=�����|<�������><���� ��������><�������>\n";
					cin >> expression;
					if (!checkCorrectExpression(expression))
					{
						cout << "������! ������������ ���������.";
						expression.clear();
						isExpressionEntered = false;
						break;
					}
					else
					{
						isExpressionEntered = true;
						tree = new Tree(expression);
					}
					break;
				}

				case PRINT:
				{
					printer->setTree(tree);
					cout << "���������, ���������� �� ������:\n";
					printer->printExpression();
					cout << "������ ���������:\n";
					printer->printTree();
					break;
				}

				case SUBTREES:
				{
					float leftSum = calculateLeftTree(tree);
					float rightSum = calculateRigthTree(tree);
					cout << "��������� � ����� ���������: " << leftSum << '\n';
					cout << "��������� � ������ ���������: " << rightSum << '\n';
					break;
				}

				case CALCULATE_TREE:
				{
					cout << "������ ������: " << tree->getRoot()->value << '\n';
					cout << "��������� ������: " << calculateTreeExpression(tree->getRoot()) << '\n';
					break;
				}

				case EXIT:
				{
					cout << "\n�� ��������!\n";
					break;
				}
			}
		}
		
		std::system("pause");
	}
	
}


bool checkCorrectExpression(string expression)
{
	if (expression.empty())
	{
		return false;
	}

	if (expression[0] > '9' || expression[0] < '0' || expression[expression.length() - 1] > '9' || expression[expression.length() - 1] < '0')
	{
		return false;
	}

	for (int i = 0; i < expression.length(); i++)
	{
		if (expression[i] > '9' || expression[i] < '0')
		{
			if (expression[i] != '+' && expression[i] != '-' && expression[i] != '*' && expression[i] != '/')
			{
				return false;
			}
		}
	}

	return true;
}