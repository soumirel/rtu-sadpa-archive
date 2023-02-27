
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

	//Переменные для пользовательского выбора.
	int userMenuChoice = -1;
	Tree* tree = nullptr;
	TreePrinter* printer = new TreePrinter();

	//Переменные для работы программы
	bool isExpressionEntered = false;
	string expression = "";

	// Главный меню-цикл.
	while (userMenuChoice != EXIT)
	{
		std::system("cls");
		cout << "Практическая работа #4 ИКБО-03-21 Мазанов А.Е. Вариант 15\n\n"
			"Задание - Деревья.\n"
			"~~~~~~~~~~~~~~~~~Меню~~~~~~~~~~~~~~~\n";
		
		if (isExpressionEntered) cout << "Текущее выражение: " << expression << '\n';
		else cout << "Выражение не задано.\n";
		
		cout << "Введите [0], чтобы задать новое выражение."
			"\nВведите [1], чтобы вывести дерево выражения."
			"\nВведите [2], чтобы вычислить значения поддеревьев."
			"\nВведите [3], чтобы вычислить значение дерева путём вычисления левого и правого подеревьев."
			"\nВведите [4], чтобы закончить работу программы."
			"\nВаш выбор: ";

		cin >> userMenuChoice;
		cin.ignore();

		if (userMenuChoice < INIT || userMenuChoice > EXIT)
		{
			cout << "Ошибка! Некорректный ввод.";
			userMenuChoice = DEFAULT;
		}

		if (userMenuChoice != DEFAULT && userMenuChoice != INIT && !isExpressionEntered)
		{
			cout << "Ошибка! Выражение не задано.";
			userMenuChoice = DEFAULT;
		}
		else 
		{
			switch (userMenuChoice)
			{
				case INIT:
				{
					cout << "Введите выражение\n"
						"Вид выражения: <формула>::=цифра|<формула><знак операции><формула>\n";
					cin >> expression;
					if (!checkCorrectExpression(expression))
					{
						cout << "Ошибка! Некорректное выражение.";
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
					cout << "Выражение, полученное из дерева:\n";
					printer->printExpression();
					cout << "Дерево выражения:\n";
					printer->printTree();
					break;
				}

				case SUBTREES:
				{
					float leftSum = calculateLeftTree(tree);
					float rightSum = calculateRigthTree(tree);
					cout << "Результат в левом поддереве: " << leftSum << '\n';
					cout << "Результат в правом поддереве: " << rightSum << '\n';
					break;
				}

				case CALCULATE_TREE:
				{
					cout << "Корень дерева: " << tree->getRoot()->value << '\n';
					cout << "Результат дерева: " << calculateTreeExpression(tree->getRoot()) << '\n';
					break;
				}

				case EXIT:
				{
					cout << "\nДо свидания!\n";
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